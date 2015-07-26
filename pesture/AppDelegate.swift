import Cocoa


@NSApplicationMain
class AppDelegate: NSObject, NSApplicationDelegate {

    @IBOutlet weak var window: NSWindow!

    func applicationDidFinishLaunching(aNotification: NSNotification) {
//        ObjCam.objShowCam();
        
        window.opaque = false;
        
        let bgColor: NSColor = NSColor(red: 1.0, green: 0.1, blue: 0.1, alpha: 0.2);
        
        window.backgroundColor = bgColor;
        
        window.movableByWindowBackground = true;
        
        window.styleMask = NSResizableWindowMask;
        
        window.contentView = MainView();
    }

    func applicationWillTerminate(aNotification: NSNotification) {
        // Insert code here to tear down your application
    }
}

