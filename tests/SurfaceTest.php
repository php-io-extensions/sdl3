<?php

declare(strict_types=1);

/*
 * Every stub declaration is what the loaded extension exposes: the stubs are
 * the source of truth, so a binding missing from the build fails here.
 */

function stubDeclarations(): array
{
    $declared = [];

    foreach (glob(__DIR__ . '/../stubs/*.stub.php') as $stub) {
        $class = null;
        foreach (file($stub) as $line) {
            if (preg_match('/^(?:final\s+)?(?:class|enum)\s+(\w+)/', $line, $m)) {
                $class = $m[1];
                $declared[$class] ??= [];
            } elseif ($class !== null && preg_match('/^\s+(?:public|private)\s+(?:static\s+)?function\s+(\w+)/', $line, $m)) {
                $declared[$class][] = $m[1];
            }
        }
    }

    return $declared;
}

it('exposes every class, enum and method the stubs declare', function (): void {
    foreach (stubDeclarations() as $class => $methods) {
        expect(class_exists($class) || enum_exists($class))->toBeTrue("{$class} is missing");

        foreach ($methods as $method) {
            expect(method_exists($class, $method))->toBeTrue("{$class}::{$method}() is missing");
        }
    }

    foreach (glob(__DIR__ . '/../stubs/*.stub.php') as $stub) {
        foreach (file($stub) as $line) {
            if (preg_match('/^function\s+(\w+)/', $line, $m)) {
                expect(function_exists($m[1]))->toBeTrue("{$m[1]}() is missing");
            } elseif (preg_match('/^const\s+(\w+)/', $line, $m)) {
                expect(defined($m[1]))->toBeTrue("{$m[1]} is missing");
            }
        }
    }
});

it('reports its version', function (): void {
    expect(phpversion('sdl3'))->toBe('0.10.0');
});
