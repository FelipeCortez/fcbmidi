////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2015 Marco Antognini (antognini.marco@gmail.com),
//                         Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "ResourcePath.hpp"
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

////////////////////////////////////////////////////////////
std::string resourcePath(void)
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    std::string rpath;
    NSBundle* bundle = [NSBundle mainBundle];

    if (bundle == nil) {
#ifdef DEBUG
        NSLog(@"bundle is nil... thus no resources path can be found.");
#endif
    } else {
        NSString* path = [bundle resourcePath];
        rpath = [path UTF8String] + std::string("/");
    }

    [pool drain];

    return rpath;
}

std::string appSupportPath(void)
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    
    std::string rpath;
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask, YES);
    NSString *applicationSupportDirectory = [paths firstObject];
    rpath = [applicationSupportDirectory UTF8String] + std::string("/fcbmidi/");
    
    [pool drain];
    
    return rpath;
}

std::string openOpenDialog(void) {
    // Loop counter.
    int i;
    
    // Create a File Open Dialog class.
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    
    // Set array of file types
    NSArray *fileTypesArray;
    fileTypesArray = [NSArray arrayWithObjects:@"jpg", @"gif", @"png", nil];
    
    // Enable options in the dialog.
    [openDlg setCanChooseFiles:YES];
    [openDlg setAllowedFileTypes:fileTypesArray];
    [openDlg setAllowsMultipleSelection:FALSE];
    
    // Display the dialog box.  If the OK pressed,
    // process the files.
    if ( [openDlg runModal] == NSOKButton ) {
        
        // Gets list of all files selected
        NSArray *files = [openDlg URLs];
        
        // Loop through the files and process them.
        for( i = 0; i < [files count]; i++ ) {
            
            // Do something with the filename.
            NSLog(@"File path: %@", [[files objectAtIndex:i] path]);
        }
        
    }
}

std::string openSaveDialog(void) {
    // Create a File Open Dialog class.
    NSSavePanel* saveDlg = [NSSavePanel savePanel];
    
    if ([saveDlg runModal] == NSOKButton ) {
        //
    }
}
