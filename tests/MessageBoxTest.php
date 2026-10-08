<?php

declare(strict_types=1);

it('shows a simple message box and returns once it is dismissed', function (): void {
    video();
    $cf = FFI::cdef('
        typedef void *CFRunLoopTimerRef; typedef void *CFRunLoopRef; typedef const void *CFStringRef;
        typedef void (*CFRunLoopTimerCallBack)(CFRunLoopTimerRef timer, void *info);
        CFRunLoopTimerRef CFRunLoopTimerCreate(void *allocator, double fireDate, double interval, unsigned long flags, long order, CFRunLoopTimerCallBack callout, void *context);
        double CFAbsoluteTimeGetCurrent(void);
        CFRunLoopRef CFRunLoopGetMain(void);
        void CFRunLoopAddTimer(CFRunLoopRef rl, CFRunLoopTimerRef timer, CFStringRef mode);
        void CFRunLoopTimerInvalidate(CFRunLoopTimerRef timer);
        void CFRelease(const void *cf);
        extern CFStringRef kCFRunLoopCommonModes;
    ', '/System/Library/Frameworks/CoreFoundation.framework/CoreFoundation');
    $shown = null;

    // While the alert runs modal, end it the way its OK button does: stop with the first button's code, then wake the loop.
    $timer = $cf->CFRunLoopTimerCreate(null, $cf->CFAbsoluteTimeGetCurrent() + 0.3, 0.1, 0, 0, function ($timer) use ($cf, &$shown): void {
        $modal = objcMsg('id objc_msgSend(id, SEL)')->objc_msgSend(nsApp(), sel('modalWindow'));
        if ($modal === null) {
            return;
        }
        $shown = true;
        $cf->CFRunLoopTimerInvalidate($timer);
        objcMsg('void objc_msgSend(id, SEL, long)')->objc_msgSend(nsApp(), sel('stopModalWithCode:'), 1000);
        $other = objcMsg('id objc_msgSend(id, SEL, unsigned long, NSPoint, unsigned long, double, long, id, short, long, long)');
        $wake = $other->objc_msgSend(objc()->objc_getClass('NSEvent'), sel('otherEventWithType:location:modifierFlags:timestamp:windowNumber:context:subtype:data1:data2:'),
            15, $other->new('NSPoint'), 0, 0.0, 0, null, 0, 0, 0);
        objcMsg('void objc_msgSend(id, SEL, id, signed char)')->objc_msgSend(nsApp(), sel('postEvent:atStart:'), $wake, 1);
    }, null);
    $cf->CFRunLoopAddTimer($cf->CFRunLoopGetMain(), $timer, $cf->kCFRunLoopCommonModes);

    $result = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 'ext-sdl3', 'The renderer could not start.', null);

    $cf->CFRunLoopTimerInvalidate($timer);
    $cf->CFRelease($timer);
    expect($shown)->toBeTrue()
        ->and($result)->toBeTrue(SDL_GetError());
})->skip(PHP_OS_FAMILY !== 'Darwin', 'the dialog is dismissed through AppKit');

it('refuses a destroyed parent window', function (): void {
    $window = hiddenWindow();
    SDL_DestroyWindow($window);

    expect(fn () => SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, 't', 'm', $window))
        ->toThrow(ValueError::class, 'SDL_Window has been destroyed')
        ->and(SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT | SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT)->toBeInt();
});
