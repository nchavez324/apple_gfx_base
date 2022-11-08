# Setup
1. Install VSCode
1. Install Bazelisk
1. Install extension llvm-vs-code-extensions.vscode-clangd
1. Install extension bazelbuild.vscode-bazel
1. Install extension xaver.clang-format
1. Configure clang-format path in User Settings
1. Install extension vadimcn.vscode-lldb

# Build
1. Run Build Task

# Debug on Mac
1. Launch DebugTestAppMacOS from VSCode

# Debug on iOS/tvOS Simulator
## Install Tulsi
1. Download Tulsi from GitHub at head
1. As of writing, Tulsi did not build with Bazel 5.0.0 (current release), so I used Bazelisk and created a `.bazelversion` file in the repo containing `6.0.0-pre.20220112.2`.
1. As of writing, Tulsi hardcoded to Xcode 13.0, so I opened `build_and_run.sh` and modified this line to `xcode_version="13.2"`.
1. Execute `./build_and_run.sh`

## Run from Xcode
1. Open `test_app/test_app.tulsiproj`
1. Generate the iOS or tvOS config
1. Run the test_app target on a simulator

# Debug on iOS/tvOS Device
## Creating Signing Resources
I won't go into the nitty gritty because stuff changes all the time, but the gist is:
1. On the Apple Developer site, create an Identifier. Usually the XC Wildcard (*) for all apps run for the team is the easiest for development. For production, consider tighter scoping.
1. Create a certificate for Apple Development which covers all platforms. Add the downloaded certificate into your login keychain via the Keychain Access app.
1. Register your devices with unambiguous names. For iOS/tvOS, grab the UUID by connecting the device to your computer and opening 'Devices & Simulators' within Xcode. The 'Identifier' is the UUID. For macOS, go to System Report, the UUID is the 'Provisioning ID'.
1. Create a Provisioning Profile, one development profile per platform, selecting the above identifier, certificate, and devices. Download it and save it to somewhere in the source tree (it is not a secret, as to use it, someone would need a copy of your certificate in their keychain).
1. Refer to it in a `(macos|ios|tvos)_application` rule via the `provisioning_profile` attribute.

## Run from Xcode
Note that `profiles/ios.mobileprovision` is scoped to:

 - App ID: Team Wildcard: UA832M7LLD.*
 - Devices: Nick's iPhone 12 Mini (Crossbones)
 - Platform: iOS
 - Certificate: Apple Development (expires 2023/01/21)

1. In Xcode go to TestApp > Targets > test_app(ios|tvos) > Signing & Capabilities
1. Select 'Nicolas Chavez' team
1. Ensure 'Automatically manage signing' is unchecked
1. Select Provisioning Profile' 'Apple iOS Development (*)'
1. Run on a device contained in the profile

One issue I got was that Bazel failed to run on device with the following error:

```
unable to find an identity on the system matching the ones in provisioning profile
```

The issue was that (and you can see this in Keychain Access) my development certificate was "not trusted". This was because Apple's WWDC certificate had expired and needed to be updated (rare):
https://developer.apple.com/support/expiration/
https://www.apple.com/certificateauthority/AppleWWDRCAG3.cer

# Refreshing Intellisense
1. Run `bazel run :refresh_compile_commands` in a terminal, which refreshes what exactly is getting built.

# GL Renderer Information
My Mac: GL Renderer: Intel(R) HD Graphics 6000 GL Version: 4.1 INTEL-18.3.5
iOS Sim: GL Renderer: Apple Software Renderer GL Version: OpenGL ES 3.0 APPLE-19.0.17
