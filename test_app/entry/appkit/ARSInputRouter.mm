#import "test_app/entry/appkit/ARSInputRouter.h"

#include <vector>

#include "test_app/input/button.hpp"
#include "test_app/input/button_event.hpp"
#include "test_app/input/pointer_event.hpp"

@implementation ARSInputRouter

- (test_app::input::Event *)routeEvent:(NSEvent *)event {
  auto timestamp = std::chrono::system_clock::now();
  switch (event.type) {
    case NSEventTypeKeyDown:
      return new test_app::input::ButtonEvent(timestamp, test_app::input::ButtonEventType::DOWN,
                                              [[self class] buttonForKeyEvent:event]);
      break;
    case NSEventTypeLeftMouseDown:
      return new test_app::input::ButtonEvent(timestamp, test_app::input::ButtonEventType::DOWN,
                                              test_app::input::Button::MOUSE_LEFT);
      break;
    case NSEventTypeRightMouseDown:
      return new test_app::input::ButtonEvent(timestamp, test_app::input::ButtonEventType::DOWN,
                                              test_app::input::Button::MOUSE_RIGHT);
      break;
    case NSEventTypeOtherMouseDown:
      return new test_app::input::ButtonEvent(timestamp, test_app::input::ButtonEventType::DOWN,
                                              test_app::input::Button::MOUSE_MIDDLE);
      break;
    case NSEventTypeKeyUp:
      return new test_app::input::ButtonEvent(timestamp, test_app::input::ButtonEventType::UP,
                                              [[self class] buttonForKeyEvent:event]);
      break;
    case NSEventTypeLeftMouseUp:
      return new test_app::input::ButtonEvent(timestamp, test_app::input::ButtonEventType::UP,
                                              test_app::input::Button::MOUSE_LEFT);
      break;
    case NSEventTypeRightMouseUp:
      return new test_app::input::ButtonEvent(timestamp, test_app::input::ButtonEventType::UP,
                                              test_app::input::Button::MOUSE_RIGHT);
      break;
    case NSEventTypeOtherMouseUp:
      return new test_app::input::ButtonEvent(timestamp, test_app::input::ButtonEventType::UP,
                                              test_app::input::Button::MOUSE_MIDDLE);
      break;
    case NSEventTypeLeftMouseDragged:
      return new test_app::input::PointerEvent(
          timestamp, glm::ivec2((int)event.locationInWindow.x, (int)event.locationInWindow.x));
      break;
    case NSEventTypeRightMouseDragged:
      return new test_app::input::PointerEvent(
          timestamp, glm::ivec2((int)event.locationInWindow.x, (int)event.locationInWindow.x));
      break;
    case NSEventTypeOtherMouseDragged:
      return new test_app::input::PointerEvent(
          timestamp, glm::ivec2((int)event.locationInWindow.x, (int)event.locationInWindow.x));
      break;
    case NSEventTypeMouseMoved:
      return new test_app::input::PointerEvent(
          timestamp, glm::ivec2((int)event.locationInWindow.x, (int)event.locationInWindow.x));
      break;
    case NSEventTypeFlagsChanged:
      break;
    default:
      break;
  }
  return nullptr;
}

+ (test_app::input::Button)buttonForKeyEvent:(NSEvent *)event {
  unichar keyChar = [event.charactersIgnoringModifiers characterAtIndex:0];
  switch (keyChar) {
    case NSLeftArrowFunctionKey:
      return test_app::input::Button::KEY_ARROW_LEFT;
    case NSRightArrowFunctionKey:
      return test_app::input::Button::KEY_ARROW_RIGHT;
    case NSUpArrowFunctionKey:
      return test_app::input::Button::KEY_ARROW_UP;
    case NSDownArrowFunctionKey:
      return test_app::input::Button::KEY_ARROW_DOWN;
  }
  return test_app::input::Button::KEY_UNKNOWN;
}

@end
