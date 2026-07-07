#!/bin/bash

# JetPack 6 / Ubuntu 22.04 (Jammy) installer for the sdl3 PHP extension.
#
# Builds SDL3 from the release-3.4.x branch (Ubuntu 22.04 has no SDL3 in apt)
# then builds the PHP extension from the pre-generated C source using phpize.
# Tested on Jetson Orin Nano (aarch64) running JetPack 6.
#
# Usage:
#   bash install-jetpack6.sh
#
# Optional env overrides:
#   PHP_BIN      — path to the php binary   (default: first php on PATH)
#   PHP_EXT_DIR  — override the install dir  (default: from php-config)

set -Eeuo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
EXTENSION_NAME="sdl3"
EXT_SRC="${SCRIPT_DIR}/ext"
BUILD_SO="${EXT_SRC}/modules/${EXTENSION_NAME}.so"
LOG_FILE="${SCRIPT_DIR}/build.log"

MIN_SDL3_VERSION="3.4.0"

if [ "${EUID:-$(id -u)}" -ne 0 ]; then
    SUDO="sudo"
else
    SUDO=""
fi

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

die() {
    echo ""
    echo "❌  $*" >&2
    exit 1
}

require_cmd() {
    command -v "$1" >/dev/null 2>&1 || die "Required command not found: $1"
}

header() {
    echo "============================================"
    echo "  SDL3 Extension Installer (JetPack 6)     "
    echo "============================================"
    echo ""
}

step() { echo "$*"; }
ok()   { echo "   ✓ $*"; }

show_failure_logs() {
    if [ -f "$LOG_FILE" ]; then
        echo ""
        echo "---- Last 100 lines of build.log ----"
        tail -100 "$LOG_FILE" || true
    fi
}

# Returns 0 if $1 >= $2 (both in x.y.z form)
version_ge() {
    local IFS=.
    local a=($1) b=($2)
    local i
    for i in 0 1 2; do
        local av="${a[$i]:-0}" bv="${b[$i]:-0}"
        if   (( av > bv )); then return 0
        elif (( av < bv )); then return 1
        fi
    done
    return 0
}

# ---------------------------------------------------------------------------
# Build SDL3 from source
# Ubuntu 22.04 does not ship SDL3 in its apt repos — always build from source.
# libxtst-dev (X11 XTEST extension) is typically absent on Jetson; skip it.
# ---------------------------------------------------------------------------

build_sdl3_from_source() {
    step "🏗️  Building SDL3 >= ${MIN_SDL3_VERSION} from source..."
    $SUDO apt-get install -y --no-install-recommends \
        build-essential cmake git \
        >>"$LOG_FILE" 2>&1 || die "Failed to install SDL3 build prerequisites."

    local tmp
    tmp="$(mktemp -d)"

    step "   Cloning SDL release-3.4.x..."
    git clone --branch release-3.4.x --depth 1 \
        https://github.com/libsdl-org/SDL "$tmp/SDL" \
        >>"$LOG_FILE" 2>&1 || die "Failed to clone SDL3 source."

    step "   Configuring..."
    cmake -S "$tmp/SDL" -B "$tmp/SDL/build" \
        -DCMAKE_BUILD_TYPE=Release \
        -DSDL_TEST=OFF \
        -DSDL_TESTS=OFF \
        -DSDL_X11_XTEST=OFF \
        -DSDL_WAYLAND=OFF \
        >>"$LOG_FILE" 2>&1 || { show_failure_logs; die "SDL3 cmake configure failed."; }

    step "   Compiling ($(nproc) cores)..."
    cmake --build "$tmp/SDL/build" --parallel "$(nproc)" \
        >>"$LOG_FILE" 2>&1 || { show_failure_logs; die "SDL3 build failed."; }

    $SUDO cmake --install "$tmp/SDL/build" \
        >>"$LOG_FILE" 2>&1 || die "SDL3 install failed."

    $SUDO ldconfig 2>/dev/null || true
    rm -rf "$tmp"

    export PKG_CONFIG_PATH="/usr/local/lib/pkgconfig:${PKG_CONFIG_PATH:-}"
}

# ---------------------------------------------------------------------------
# SDL3 dependency check
# ---------------------------------------------------------------------------

ensure_sdl3() {
    step "📚 Checking SDL3 dependency (minimum ${MIN_SDL3_VERSION})..."

    export PKG_CONFIG_PATH="/usr/local/lib/pkgconfig:${PKG_CONFIG_PATH:-}"

    if command -v pkg-config >/dev/null 2>&1 && pkg-config --exists sdl3 2>/dev/null; then
        local ver
        ver="$(pkg-config --modversion sdl3)"
        if version_ge "$ver" "$MIN_SDL3_VERSION"; then
            ok "SDL3 ${ver} already installed and meets minimum"
            return
        fi
        echo "   ⚠️  SDL3 ${ver} found but < ${MIN_SDL3_VERSION} — rebuilding from source."
    else
        step "   SDL3 not found — building from source (Ubuntu 22.04 has no SDL3 in apt)."
    fi

    build_sdl3_from_source

    export PKG_CONFIG_PATH="/usr/local/lib/pkgconfig:${PKG_CONFIG_PATH:-}"
    pkg-config --exists sdl3 2>/dev/null \
        || die "SDL3 still not detected after source build. Check /usr/local/lib/pkgconfig."

    ok "SDL3 $(pkg-config --modversion sdl3) ready"
}

ensure_opengl_runtime_jetpack() {
    step "🖼️  Verifying NVIDIA OpenGL/EGL/GLES runtime stack..."

    if ! command -v ldconfig >/dev/null 2>&1; then
        die "ldconfig is required to verify JetPack OpenGL runtime libraries."
    fi

    local cache
    cache="$(ldconfig -p 2>/dev/null || true)"
    echo "$cache" | grep -q "libGL.so" || die "Missing libGL.so in linker cache; JetPack OpenGL runtime looks incomplete."
    echo "$cache" | grep -q "libEGL.so" || die "Missing libEGL.so in linker cache; JetPack EGL runtime looks incomplete."
    echo "$cache" | grep -q "libGLESv2.so" || die "Missing libGLESv2.so in linker cache; JetPack GLES runtime looks incomplete."

    if echo "$cache" | grep -qi "nvidia"; then
        ok "NVIDIA GL stack detected in linker cache"
    else
        ok "Core GL/EGL/GLES libs detected (NVIDIA tag not explicit in cache output)"
    fi
}

# ---------------------------------------------------------------------------
# PHP dev headers check
# ---------------------------------------------------------------------------

ensure_php_dev() {
    step "🐘 Checking PHP dev headers..."

    if command -v phpize >/dev/null 2>&1; then
        ok "phpize found: $(command -v phpize)"
        return
    fi

    local ver
    ver="$(${PHP_BIN:-php} -r 'echo PHP_MAJOR_VERSION.".".PHP_MINOR_VERSION;' 2>/dev/null || true)"

    step "   phpize not found — installing PHP dev headers..."
    $SUDO apt-get update -q >>"$LOG_FILE" 2>&1
    local installed=0
    for pkg in "php${ver}-dev" "php-dev"; do
        if $SUDO apt-get install -y --no-install-recommends "$pkg" \
            >>"$LOG_FILE" 2>&1; then
            installed=1
            ok "Installed $pkg"
            break
        fi
    done
    [ "$installed" -eq 1 ] || die "Could not install PHP dev headers."
    command -v phpize >/dev/null 2>&1 || die "phpize still not found after install."
    ok "phpize ready"
}

# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

header

# Preflight
step "🔎 Preflight checks..."

PHP_BIN="${PHP_BIN:-$(command -v php || true)}"
[ -x "$PHP_BIN" ] || die "PHP not found. Install PHP first."
ok "PHP binary: $PHP_BIN ($("$PHP_BIN" -r 'echo PHP_VERSION;'))"

require_cmd gcc
require_cmd make
ok "gcc / make present"

ensure_php_dev
ensure_sdl3
ensure_opengl_runtime_jetpack

# ---------------------------------------------------------------------------
# Locate php-config and extension dir
# ---------------------------------------------------------------------------

PHP_VER_MM="$("$PHP_BIN" -r 'echo PHP_MAJOR_VERSION.".".PHP_MINOR_VERSION;')"
PHP_VER_NN="$("$PHP_BIN" -r 'echo PHP_MAJOR_VERSION.PHP_MINOR_VERSION;')"

PHP_BIN_DIR="$(dirname "$(realpath "$PHP_BIN")")"
PHP_CONFIG="${PHP_BIN_DIR}/php-config"
[ -x "$PHP_CONFIG" ] || PHP_CONFIG="$(command -v php-config 2>/dev/null || true)"
[ -x "$PHP_CONFIG" ] || die "php-config not found. Try: sudo apt-get install php${PHP_VER_MM}-dev"

if [ -z "${PHP_EXT_DIR:-}" ]; then
    PHP_EXT_DIR="$("$PHP_CONFIG" --extension-dir)"
fi
[ -n "$PHP_EXT_DIR" ] || die "Could not determine PHP extension dir."

PHP_PHPIZE="${PHP_BIN_DIR}/phpize"
[ -x "$PHP_PHPIZE" ] || PHP_PHPIZE="$(command -v phpize)"

CLI_SCAN_DIR="$("$PHP_BIN" --ini 2>/dev/null \
    | awk -F': ' '/Scan for additional \.ini files in:/{print $2}' || true)"

ok "PHP version    : ${PHP_VER_MM}"
ok "Extension dir  : ${PHP_EXT_DIR}"
ok "phpize         : ${PHP_PHPIZE}"
[ -n "$CLI_SCAN_DIR" ] && ok "INI scan dir   : ${CLI_SCAN_DIR}"
echo ""

# ---------------------------------------------------------------------------
# Clean previous build artifacts
# ---------------------------------------------------------------------------

step "🧹 Cleaning previous build artifacts..."
cd "$EXT_SRC"

if [ -f Makefile ]; then
    make distclean >>"$LOG_FILE" 2>&1 || true
fi
"$PHP_PHPIZE" --clean >>"$LOG_FILE" 2>&1 || true
ok "ext/ cleaned"
echo ""

# ---------------------------------------------------------------------------
# Configure + Build
# ---------------------------------------------------------------------------

# GCC 11 on Ubuntu 22.04 is generally lenient, but set safe flags anyway.
export CFLAGS="${CFLAGS:-} -Wno-error -Wno-error=incompatible-pointer-types -Wno-pointer-compare"
export CPPFLAGS="${CPPFLAGS:-} -Wno-error -Wno-error=incompatible-pointer-types"
# Source-built SDL3 lands in /usr/local; make sure configure picks it up.
export PKG_CONFIG_PATH="/usr/local/lib/pkgconfig:${PKG_CONFIG_PATH:-}"

step "⚙️  Running phpize..."
"$PHP_PHPIZE" >>"$LOG_FILE" 2>&1 || { show_failure_logs; die "phpize failed."; }
ok "phpize complete"

step "⚙️  Configuring (--enable-sdl3)..."
./configure --with-php-config="$PHP_CONFIG" --enable-sdl3 \
    >>"$LOG_FILE" 2>&1 || { show_failure_logs; die "./configure failed."; }
ok "configure complete"
echo ""

step "🔨 Building extension ($(nproc) cores)..."
make -j"$(nproc)" >>"$LOG_FILE" 2>&1 || { show_failure_logs; die "make failed. See ${LOG_FILE}."; }

[ -f "$BUILD_SO" ] || { show_failure_logs; die "Build succeeded but ${BUILD_SO} not found."; }
ok "Build complete → ${BUILD_SO}"
echo ""

# ---------------------------------------------------------------------------
# Install .so
# ---------------------------------------------------------------------------

step "📦 Installing binary..."
$SUDO mkdir -p "$PHP_EXT_DIR"
$SUDO cp -f "$BUILD_SO" "${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
$SUDO chmod 755 "${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
ok "Installed → ${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
echo ""

# ---------------------------------------------------------------------------
# Enable extension (write .ini into every detected conf.d)
# ---------------------------------------------------------------------------

step "⚙️  Enabling extension..."

declare -a CONF_CANDIDATES=()
[ -n "$CLI_SCAN_DIR" ] && [ "$CLI_SCAN_DIR" != "(none)" ] && [ -d "$CLI_SCAN_DIR" ] \
    && CONF_CANDIDATES+=("$CLI_SCAN_DIR")

for d in \
    "/etc/php/${PHP_VER_MM}/cli/conf.d" \
    "/etc/php/${PHP_VER_MM}/fpm/conf.d" \
    "/etc/php/${PHP_VER_MM}/apache2/conf.d"; do
    [ -d "$d" ] && CONF_CANDIDATES+=("$d")
done

# Deduplicate
CONF_DIRS=()
while IFS= read -r _dir; do
    CONF_DIRS+=("$_dir")
done < <(printf "%s\n" "${CONF_CANDIDATES[@]}" | awk '!seen[$0]++')

INI_NAME="30-${EXTENSION_NAME}.ini"
INI_CONTENT="extension=${PHP_EXT_DIR}/${EXTENSION_NAME}.so"

if [ "${#CONF_DIRS[@]}" -eq 0 ]; then
    echo "   ⚠️  No conf.d directories found. Enabling for CLI context only."
fi

for confd in "${CONF_DIRS[@]:-}"; do
    echo "$INI_CONTENT" | $SUDO tee "${confd}/${INI_NAME}" >/dev/null
    ok "Written: ${confd}/${INI_NAME}"
done
echo ""

# ---------------------------------------------------------------------------
# Verify
# ---------------------------------------------------------------------------

step "🔍 Verifying installation (CLI)..."
if "$PHP_BIN" -m 2>/dev/null | grep -q "^${EXTENSION_NAME}$"; then
    ok "Extension loaded successfully"
else
    die "Extension not detected by PHP. Check php --ini and ${INI_NAME} placement."
fi
echo ""

step "============================================"
step " Extension Information"
step "============================================"
"$PHP_BIN" --ri "${EXTENSION_NAME}" || true
echo ""

# ---------------------------------------------------------------------------
# Reload FPM if running
# ---------------------------------------------------------------------------

if command -v systemctl >/dev/null 2>&1; then
    for svc in "php${PHP_VER_MM}-fpm" "php-fpm"; do
        if systemctl is-active --quiet "${svc}.service" 2>/dev/null; then
            step "🔁 Reloading ${svc}..."
            $SUDO systemctl reload "${svc}" || true
            ok "${svc} reloaded"
            break
        fi
    done
fi

# ---------------------------------------------------------------------------
# Done
# ---------------------------------------------------------------------------

echo "✅  Installation complete!"
echo ""
echo "File locations:"
echo "  • Binary : ${PHP_EXT_DIR}/${EXTENSION_NAME}.so"
if [ "${#CONF_DIRS[@]}" -gt 0 ]; then
    for d in "${CONF_DIRS[@]}"; do
        echo "  • Config : ${d}/${INI_NAME}"
    done
else
    echo "  • Config : (check php --ini)"
fi
echo ""
echo "Run the proof-of-work example:"
echo "  php ${SCRIPT_DIR}/examples/proof_of_work.php"
echo ""
