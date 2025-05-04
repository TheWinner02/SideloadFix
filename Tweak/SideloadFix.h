#include <dlfcn.h>
#include <mach-o/dyld.h>
#include <objc/runtime.h>
#include <Foundation/Foundation.h>

#include "fishhook/fishhook.h"

static NSString *originalAppName;
static NSString *originalBundleID;
static NSURL *fakeGroupContainerURL;
static NSString *keychainAccessGroup;

static OSStatus (*orig_SecItemDelete)(CFDictionaryRef);
static OSStatus (*orig_SecItemAdd)(CFDictionaryRef, CFTypeRef*);
static OSStatus (*orig_SecItemUpdate)(CFDictionaryRef, CFDictionaryRef);
static OSStatus (*orig_SecItemCopyMatching)(CFDictionaryRef, CFTypeRef*);

@interface NSFileManager (SideloadedFixes)

- (NSURL*)swizzled_containerURLForSecurityApplicationGroupIdentifier:(NSString*)groupIdentifier;

@end
