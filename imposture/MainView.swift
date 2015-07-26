import Cocoa


class MainView: NSView {
    let headColor: NSColor = NSColor.redColor();

    override func drawRect(dirtyRect: NSRect) {
        super.drawRect(dirtyRect)

        headColor.setFill();

        var headRect: NSRect = NSRect();
        headRect.origin.x = 3;
        headRect.origin.y = 20;
        headRect.size.width = bounds.width - 6;
        headRect.size.height = 10;
        
        NSRectFill(headRect);
    }
    
}
