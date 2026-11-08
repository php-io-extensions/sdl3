<?php

declare(strict_types=1);

it('shows a simple message box and returns once it is dismissed', function (): void {
    video();
    $shown = null;
    $app = NSApplication::sharedApplication();

    // While the alert runs modal, end it the way its OK button does: stop with the first button's code, then wake the loop.
    $target = new ObjCTarget(function (?NSObject $timer) use ($app, &$shown): void {
        if ($app->modalWindow() === null) {
            return;
        }
        $shown = true;
        $timer->invalidate();
        $app->stopModalWithCode(1000);
        $app->postEventAtStart(NSEvent::otherEventWithTypeLocationModifierFlagsTimestampWindowNumberContextSubtypeData1Data2(
            NSEventType::APPLICATION_DEFINED, new NSPoint(0.0, 0.0), 0, 0.0, 0, null, 0, 0, 0), true);
    });
    // (common modes: a modal session runs its own loop mode)
    $timer = NSTimer::timerWithTimeIntervalTargetSelectorUserInfoRepeats(0.1, $target, ObjCTarget::ACTION, null, true);
    NSRunLoop::mainRunLoop()->addTimerForMode($timer, NSRunLoopCommonModes);

    $result = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 'ext-sdl3', 'The renderer could not start.', null);

    $timer->invalidate();
    expect($shown)->toBeTrue()
        ->and($result)->toBeTrue(SDL_GetError());
})->skip(PHP_OS_FAMILY !== 'Darwin' || ! extension_loaded('appkit'), 'the dialog is dismissed through ext-appkit');

// A destroyed parent window is NULL, which SDL takes as no parent: the box would open and wait, so it is not shown here.
it('combines the message box flags', function (): void {
    expect(SDL_MESSAGEBOX_WARNING | SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT | SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT)->toBeInt();
});
