/*
 Copyright (c) 2011, OpenEmu Team
 
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
     * Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
     * Neither the name of the OpenEmu Team nor the
       names of its contributors may be used to endorse or promote products
       derived from this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY OpenEmu Team ''AS IS'' AND ANY
 EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL OpenEmu Team BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <Foundation/Foundation.h>
#import <OpenEmuBase/OEPluginController.h>

@class OEHIDEvent;
@class OESystemResponder;

extern NSString *const OESettingValueKey;
extern NSString *const OEHIDEventValueKey;
extern NSString *const OEHIDEventExtraValueKey;
extern NSString *const OEKeyboardEventValueKey;
extern NSString *const OEControlsPreferenceKey;
extern NSString *const OESystemPluginName;
extern NSString *const OESystemName;
extern NSString *const OESystemIdentifier;
extern NSString *const OESystemIconName;
extern NSString *const OEProjectURLKey;
extern NSString *const OEArchiveIDs;
extern NSString *const OEFileTypes;

extern NSString *const OEGenericControlNamesKey;

// NSDictionary - contains OEHatSwitchControlsKey and OEAxisControlsKey keys
extern NSString *const OEControlTypesKey;
// NSArray - contains strings that are also contained in OEGenericControlNamesKey array
// They represent keys that should be linked together if one of them were to be associated with a hat switch event
// The order of the key follows the rotation order: i.e. [ up, right, down, left ]
extern NSString *const OEHatSwitchControlsKey;
// NSArray - contains strings that are also contained in OEGenericControlNamesKey array
// They represent keys that are the opposite of each other on an axis and
// should be associated together if one of them was associated to an axis event
extern NSString *const OEAxisControlsKey;

/* OEControlListKey plist format:
 * <array>                                        <!-- Page list -->
 *   <array>                                      <!-- One Page with columns in it -->
 *     <array>                                    <!-- One column with keys in it -->
 *       <string>D-Pad</string>                   <!-- One column label
 *       <dict>                                   <!-- One control with its data -->
 *         <key>OEControlListKeyNameKey</key>
 *         <string>OESMSButtonUp[@]</string>
 *         <key>OEControlListKeyLabelKey</key>
 *         <string>Up</string>                    <!-- The colon is added by the app -->
 *         <key>OEControlListKeyPositionKey</key>
 *         <string>{195, 176}</string>            <!-- Format generated by NSStringFromPoint() -->
 *       </dict>
 *       <string>-</string>                       <!-- line separator -->
 *     </array>
 *   </array>
 * </array>
 */

extern NSString *const OEControlListKey;
extern NSString *const OEControlListKeyNameKey;
extern NSString *const OEControlListKeyLabelKey;
extern NSString *const OEControlListKeyPositionKey;

extern NSString *const OEControllerImageKey;       // NSString - file name of the controller image
extern NSString *const OEControllerImageMaskKey;   // NSString - file name of the controller image mask
extern NSString *const OEControllerKeyPositionKey; // NSDictionary - KeyName -> NSPoint as NSString

@interface OESystemController : NSObject <OEPluginController>

/*
  *The method search for a class associated with aKey and instantiate the controller
  *with the default Nib name provided by the key.
  *
  *For example: if the passed-in key is @"OEControlsPreferenceKey" the default nib name will be
  *@"ControlsPreference" (the two-letter prefix "OE" and three-letter suffix "Key" are removed from
  *the name).
 */
- (id)newPreferenceViewControllerForKey:(NSString *)aKey;

// A dictionary of keys and UIViewController classes, keys are different panels available in the preferences
// Must be overridden by subclasses to provide the appropriate classes
- (NSDictionary *)preferenceViewControllerClasses;


@property(readonly, copy) NSString     *systemIdentifier;
@property(readonly)       NSString     *systemName;
@property(readonly)       NSImage      *systemIcon;

@property(readonly)       NSUInteger    numberOfPlayers;
@property(readonly)       Class         responderClass;
@property(readonly, copy) NSArray      *genericSettingNames;
@property(readonly, copy) NSArray      *genericControlNames;
@property(readonly, copy) NSString     *playerString;

@property(readonly, copy) NSArray      *controlPageList;
@property(readonly, copy) NSDictionary *controllerKeyPositions;
@property(readonly, copy) NSString     *controllerImageName;
@property(readonly, copy) NSString     *controllerImageMaskName;

@property(readonly, copy) NSImage      *controllerImage;
@property(readonly, copy) NSImage      *controllerImageMask;

- (NSString *)genericKeyForKey:(NSString *)keyName getKeyIndex:(NSUInteger *)keyIndex playerNumber:(NSUInteger *)playerNumber;

- (NSUInteger)keyIndexForKey:(NSString *)keyName getPlayerNumber:(NSUInteger *)playerNumber DEPRECATED_ATTRIBUTE;
- (NSUInteger)playerNumberInKey:(NSString *)keyName getKeyIndex:(NSUInteger *)idx DEPRECATED_ATTRIBUTE;

#pragma mark -
#pragma mark Bindings settings

// Dictionary containing the default values to register for the system
@property(readonly) NSDictionary *defaultControls;
- (void)registerDefaultControls;

// Converts anObject, usually representing an event, into a value registerable into the defaults
- (id)registarableValueWithObject:(id)anObject;

// Returns the keyPath associating the key name to the type of the value
- (NSString *)keyPathForKey:(NSString *)keyName withValueType:(NSString *)aType;

// Register an event into the user defaults
// The keypath should be built using -keyPathForKey:withValueType:
- (void)registerValue:(id)aValue forKeyPath:(NSString *)keyPath;

- (NSString *)playerKeyForKey:(NSString *)aKey player:(NSUInteger)playerNumber;
- (id)settingForKey:(NSString *)keyName;
- (id)HIDEventForKey:(NSString *)keyName;
- (id)keyboardEventForKey:(NSString *)keyName;
- (void)registerSetting:(id)settingValue forKey:(NSString *)keyName;
- (void)registerEvent:(OEHIDEvent *)theEvent forKey:(NSString *)keyName;

// The block is not called if the key is not part of a hat switch key type
// The keyIndex in the enumerator is the same as the index in -genericControlNames array
// The keys are enumerated in the order they appear in the OEHatSwitchControlsKey array
- (BOOL)enumerateKeysLinkedToHatSwitchKey:(NSString *)aKey usingBlock:(void(^)(NSString *key, NSUInteger keyIdx, BOOL *stop))block;
// Same as above except it takes a non-generic key
- (BOOL)enumeratePlayersKeysLinkedToHatSwitchKey:(NSString *)aKey usingBlock:(void(^)(NSString *key, NSUInteger keyIdx, BOOL *stop))block;
// The method returns nil if the key is not associated with an axis
- (NSString *)oppositeKeyForAxisKey:(NSString *)aKey getKeyIndex:(NSUInteger *)keyIndex;
// Same as above except it takes a non-generic key
- (NSString *)oppositePlayerKeyForAxisKey:(NSString *)aKey getKeyIndex:(NSUInteger *)keyIndex;

#pragma mark -
#pragma mark Game System Responder objects

- (id)newGameSystemResponder;
- (void)registerGameSystemResponder:(OESystemResponder *)responder;
- (void)unregisterGameSystemResponder:(OESystemResponder *)responder;

#pragma mark -
#pragma mark ROM Handling
@property(readonly, strong) NSArray *fileTypes;
@property(readonly, strong) NSArray *archiveIDs;

- (BOOL)canHandleFile:(NSString*)path;

@end
