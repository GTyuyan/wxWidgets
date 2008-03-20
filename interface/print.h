/////////////////////////////////////////////////////////////////////////////
// Name:        print.h
// Purpose:     interface of wxPreviewControlBar
// Author:      wxWidgets team
// RCS-ID:      $Id$
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

/**
    @class wxPreviewControlBar
    @wxheader{print.h}

    This is the default implementation of the preview control bar, a panel
    with buttons and a zoom control. You can derive a new class from this and
    override some or all member functions to change the behaviour and appearance;
    or you can leave it as it is.

    @library{wxbase}
    @category{printing}

    @see wxPreviewFrame, wxPreviewCanvas, wxPrintPreview
*/
class wxPreviewControlBar : public wxPanel
{
public:
    /**
        Destructor.
    */
    ~wxPreviewControlBar();

    /**
        Creates buttons, according to value of the button style flags.
    */
    void CreateButtons();

    /**
        Gets the print preview object associated with the control bar.
    */
    wxPrintPreview* GetPrintPreview();

    /**
        Gets the current zoom setting in percent.
    */
    int GetZoomControl();

    /**
        Sets the zoom control.
    */
    void SetZoomControl(int percent);

    /**
        Constructor.
        The buttons parameter may be a combination of the following, using the bitwise
        'or' operator.

        wxPREVIEW_PRINT

        Create a print button.

        wxPREVIEW_NEXT

        Create a next page button.

        wxPREVIEW_PREVIOUS

        Create a previous page button.

        wxPREVIEW_ZOOM

        Create a zoom control.

        wxPREVIEW_DEFAULT

        Equivalent to a combination of wxPREVIEW_PREVIOUS, wxPREVIEW_NEXT and
        wxPREVIEW_ZOOM.
    */
    wxPreviewControlBar(wxPrintPreview* preview, long buttons,
                        wxWindow* parent,
                        const wxPoint& pos = wxDefaultPosition,
                        const wxSize& size = wxDefaultSize,
                        long style = 0,
                        const wxString& name = "panel");
};



/**
    @class wxPreviewCanvas
    @wxheader{print.h}

    A preview canvas is the default canvas used by the print preview
    system to display the preview.

    @library{wxbase}
    @category{printing}

    @see wxPreviewFrame, wxPreviewControlBar, wxPrintPreview
*/
class wxPreviewCanvas : public wxScrolledWindow
{
public:
    /**
        Constructor.
    */
    wxPreviewCanvas(wxPrintPreview* preview, wxWindow* parent,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = 0,
                    const wxString& name = "canvas");

    /**
        Destructor.
    */
    ~wxPreviewCanvas();

    /**
        Calls wxPrintPreview::PaintPage to refresh the canvas.
    */
    void OnPaint(wxPaintEvent& event);
};



/**
    @class wxPreviewFrame
    @wxheader{print.h}

    This class provides the default method of managing the print preview interface.
    Member functions may be overridden to replace functionality, or the
    class may be used without derivation.

    @library{wxbase}
    @category{printing}

    @see wxPreviewCanvas, wxPreviewControlBar, wxPrintPreview
*/
class wxPreviewFrame : public wxFrame
{
public:
    /**
        Constructor. Pass a print preview object plus other normal frame arguments.
        The print preview object will be destroyed by the frame when it closes.
    */
    wxPreviewFrame(wxPrintPreview* preview, wxWindow* parent,
                   const wxString& title,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size size = wxDefaultSize,
                   long style = wxDEFAULT_FRAME_STYLE,
                   const wxString& name = "frame");

    /**
        Destructor.
    */
    ~wxPreviewFrame();

    /**
        Creates a wxPreviewCanvas. Override this function to allow
        a user-defined preview canvas object to be created.
    */
    void CreateCanvas();

    /**
        Creates a wxPreviewControlBar. Override this function to allow
        a user-defined preview control bar object to be created.
    */
    void CreateControlBar();

    /**
        Creates the preview canvas and control bar, and calls
        wxWindow::MakeModal(@true) to disable other top-level windows
        in the application.
        This function should be called by the application prior to
        showing the frame.
    */
    void Initialize();

    /**
        Enables the other frames in the application, and deletes the print preview
        object, implicitly deleting any printout objects associated with the print
        preview object.
    */
    void OnCloseWindow(wxCloseEvent& event);
};



/**
    @class wxPrintPreview
    @wxheader{print.h}

    Objects of this class manage the print preview process. The object is passed
    a wxPrintout object, and the wxPrintPreview object itself is passed to
    a wxPreviewFrame object. Previewing is started by initializing and showing
    the preview frame. Unlike wxPrinter::Print, flow of control returns to the
    application
    immediately after the frame is shown.

    @library{wxbase}
    @category{printing}

    @see @ref overview_printingoverview "Printing framework overview", wxPrinterDC,
    wxPrintDialog, wxPrintout, wxPrinter, wxPreviewCanvas, wxPreviewControlBar, wxPreviewFrame.
*/
class wxPrintPreview : public wxObject
{
public:
    /**
        Constructor. Pass a printout object, an optional printout object to be
        used for actual printing, and the address of an optional
        block of printer data, which will be copied to the print preview object's
        print data.
        If @a printoutForPrinting is non-@NULL, a @b Print... button will be placed on
        the
        preview frame so that the user can print directly from the preview interface.
        Do not explicitly delete the printout objects once this destructor has been
        called, since they will be deleted in the wxPrintPreview constructor.
        The same does not apply to the @a data argument.
        Test the Ok member to check whether the wxPrintPreview object was created
        correctly.
        Ok could return @false if there was a problem initializing the printer device
        context
        (current printer not set, for example).
    */
    wxPrintPreview(wxPrintout* printout,
                   wxPrintout* printoutForPrinting,
                   wxPrintData* data = NULL);

    /**
        Destructor. Deletes both print preview objects, so do not destroy these objects
        in your application.
    */
    ~wxPrinter();

    /**
        Gets the preview window used for displaying the print preview image.
    */
    wxPreviewCanvas* GetCanvas();

    /**
        Gets the page currently being previewed.
    */
    int GetCurrentPage();

    /**
        Gets the frame used for displaying the print preview canvas
        and control bar.
    */
    wxFrame* GetFrame();

    /**
        Returns the maximum page number.
    */
    int GetMaxPage();

    /**
        Returns the minimum page number.
    */
    int GetMinPage();

    /**
        Gets the preview printout object associated with the wxPrintPreview object.
    */
    wxPrintout* GetPrintout();

    /**
        Gets the printout object to be used for printing from within the preview
        interface,
        or @NULL if none exists.
    */
    wxPrintout* GetPrintoutForPrinting();

    /**
        Returns @true if the wxPrintPreview is valid, @false otherwise. It could return
        @false if there was a
        problem initializing the printer device context (current printer not set, for
        example).
    */
    bool Ok();

    /**
        This refreshes the preview window with the preview image.
        It must be called from the preview window's OnPaint member.
        The implementation simply blits the preview bitmap onto
        the canvas, creating a new preview bitmap if none exists.
    */
    bool PaintPage(wxPreviewCanvas* canvas, wxDC dc);

    /**
        Invokes the print process using the second wxPrintout object
        supplied in the wxPrintPreview constructor.
        Will normally be called by the @b Print... panel item on the
        preview frame's control bar.
        Returns @false in case of error -- call
        wxPrinter::GetLastError to get detailed
        information about the kind of the error.
    */
    bool Print(bool prompt);

    /**
        Renders a page into a wxMemoryDC. Used internally by wxPrintPreview.
    */
    bool RenderPage(int pageNum);

    /**
        Sets the window to be used for displaying the print preview image.
    */
    void SetCanvas(wxPreviewCanvas* window);

    /**
        Sets the current page to be previewed.
    */
    void SetCurrentPage(int pageNum);

    /**
        Sets the frame to be used for displaying the print preview canvas
        and control bar.
    */
    void SetFrame(wxFrame* frame);

    /**
        Associates a printout object with the wxPrintPreview object.
    */
    void SetPrintout(wxPrintout* printout);

    /**
        Sets the percentage preview zoom, and refreshes the preview canvas
        accordingly.
    */
    void SetZoom(int percent);
};



/**
    @class wxPrinter
    @wxheader{print.h}

    This class represents the Windows or PostScript printer, and is the vehicle
    through
    which printing may be launched by an application. Printing can also
    be achieved through using of lower functions and classes, but
    this and associated classes provide a more convenient and general
    method of printing.

    @library{wxbase}
    @category{printing}

    @see @ref overview_printingoverview "Printing framework overview", wxPrinterDC,
    wxPrintDialog, wxPrintout, wxPrintPreview.
*/
class wxPrinter : public wxObject
{
public:
    /**
        Constructor. Pass an optional pointer to a block of print
        dialog data, which will be copied to the printer object's local data.

        @see wxPrintDialogData, wxPrintData
    */
    wxPrinter(wxPrintDialogData* data = NULL);

    /**
        Creates the default printing abort window, with a cancel button.
    */
    void CreateAbortWindow(wxWindow* parent, wxPrintout* printout);

    /**
        Returns @true if the user has aborted the print job.
    */
    bool GetAbort();

    /**
        Return last error. Valid after calling Print(),
        PrintDialog() or
        wxPrintPreview::Print. These functions
        set last error to @b wxPRINTER_NO_ERROR if no error happened.
        Returned value is one of the following:

        @b wxPRINTER_NO_ERROR

        No error happened.

        @b wxPRINTER_CANCELLED

        The user cancelled printing.

        @b wxPRINTER_ERROR

        There was an error during printing.
    */
    static wxPrinterError GetLastError();

    /**
        Returns the @ref overview_wxprintdata "print data" associated with the printer
        object.
    */
    wxPrintDialogData GetPrintDialogData();

    /**
        Starts the printing process. Provide a parent window, a user-defined wxPrintout
        object which controls
        the printing of a document, and whether the print dialog should be invoked
        first.
        Print could return @false if there was a problem initializing the printer device
        context
        (current printer not set, for example) or the user cancelled printing. Call
        GetLastError() to get detailed
        information about the kind of the error.
    */
    bool Print(wxWindow* parent, wxPrintout* printout,
               bool prompt = true);

    /**
        Invokes the print dialog. If successful (the user did not press Cancel
        and no error occurred), a suitable device context will be returned
        (otherwise @NULL is returned -- call
        GetLastError() to get detailed
        information about the kind of the error).
        The application must delete this device context to avoid a memory leak.
    */
    wxDC* PrintDialog(wxWindow* parent);

    /**
        Default error-reporting function.
    */
    void ReportError(wxWindow* parent, wxPrintout* printout,
                     const wxString& message);

    /**
        Invokes the print setup dialog. Note that the setup dialog is obsolete from
        Windows 95, though retained for backward compatibility.
    */
    bool Setup(wxWindow* parent);
};



/**
    @class wxPrintout
    @wxheader{print.h}

    This class encapsulates the functionality of printing out an application
    document. A new class must be derived and members overridden to respond to calls
    such as OnPrintPage and HasPage and to render the print image onto an associated
    wxDC. Instances of this class are passed to wxPrinter::Print or
    to a wxPrintPreview object to initiate printing or previewing.

    Your derived wxPrintout is responsible for drawing both the preview image and
    the printed page. If your windows' drawing routines accept an arbitrary DC as an
    argument, you can re-use those routines within your wxPrintout subclass to draw
    the printout image. You may also add additional drawing elements within your
    wxPrintout subclass, like headers, footers, and/or page numbers. However, the
    image on the printed page will often differ from the image drawn on the screen,
    as will the print preview image -- not just in the presence of headers and
    footers, but typically in scale. A high-resolution printer presents a much
    larger drawing surface (i.e., a higher-resolution DC); a zoomed-out preview
    image presents a much smaller drawing surface (lower-resolution DC). By using
    the routines FitThisSizeToXXX() and/or MapScreenSizeToXXX() within your
    wxPrintout subclass to set the user scale and origin of the associated DC, you
    can easily use a single drawing routine to draw on your application's windows,
    to create the print preview image, and to create the printed paper image, and
    achieve a common appearance to the preview image and the printed page.

    @library{wxbase}
    @category{printing}

    @see @ref overview_printingoverview "Printing framework overview", wxPrinterDC,
    wxPrintDialog, wxPageSetupDialog, wxPrinter, wxPrintPreview
*/
class wxPrintout : public wxObject
{
public:
    /**
        Constructor. Pass an optional title argument - the current filename would be a
        good idea. This will appear in the printing list
        (at least in MSW)
    */
    wxPrintout(const wxString& title = "Printout");

    /**
        Destructor.
    */
    ~wxPrintout();

    /**
        Set the user scale and device origin of the wxDC associated with this wxPrintout
        so that the given image size fits entirely within the page rectangle and the
        origin is at the top left corner of the page rectangle. On MSW and Mac, the page
        rectangle is the printable area of the page. On other platforms and PostScript
        printing, the page rectangle is the entire paper. Use this if you want your
        printed image as large as possible, but with the caveat that on some platforms,
        portions of the image might be cut off at the edges.
    */
    void FitThisSizeToPage(const wxSize& imageSize);

    /**
        Set the user scale and device origin of the wxDC associated with this wxPrintout
        so that the given image size fits entirely within the page margins set in the
        given wxPageSetupDialogData object. This function provides the greatest
        consistency across all platforms because it does not depend on having access to
        the printable area of the paper. Note that on Mac, the native wxPageSetupDialog
        does not let you set the page margins; you'll have to provide your own
        mechanism,
        or you can use the Mac-only class wxMacPageMarginsDialog.
    */
    void FitThisSizeToPageMargins(const wxSize& imageSize,
                                  const wxPageSetupDialogData& pageSetupData);

    /**
        Set the user scale and device origin of the wxDC associated with this wxPrintout
        so that the given image size fits entirely within the paper and the origin is at
        the top left corner of the paper. Note that with most printers, the region
        around the edges of the paper are not printable so that the edges of the image
        could be cut off. Use this if you're managing your own page margins.
    */
    void FitThisSizeToPaper(const wxSize& imageSize);

    /**
        Returns the device context associated with the printout (given to the printout
        at start of
        printing or previewing). This will be a wxPrinterDC if printing under Windows
        or Mac,
        a wxPostScriptDC if printing on other platforms, and a wxMemoryDC if previewing.
    */
    wxDC* GetDC();

    /**
        Return the rectangle corresponding to the page margins specified by the given
        wxPageSetupDialogData object in the associated wxDC's logical coordinates for
        the
        current user scale and device origin. The page margins are specified
        with respect to the edges of the paper on all platforms.
    */
    wxRect GetLogicalPageMarginsRect(const wxPageSetupDialogData& pageSetupData);

    /**
        Return the rectangle corresponding to the page in the associated wxDC's
        logical coordinates for the current user scale and device origin.
        On MSW and Mac, this will be the printable area of the paper. On other platforms
        and PostScript printing, this will be the full paper rectangle.
    */
    wxRect GetLogicalPageRect();

    /**
        Return the rectangle corresponding to the paper in the associated wxDC's
        logical coordinates for the current user scale and device origin.
    */
    wxRect GetLogicalPaperRect();

    /**
        Returns the number of pixels per logical inch of the printer device context.
        Dividing the printer PPI by the screen PPI can give a suitable scaling factor
        for drawing text onto the printer. Remember to multiply this by a scaling factor
        to take the preview DC size into account. Or you can just use the
        FitThisSizeToXXX() and MapScreenSizeToXXX routines below, which do most of the
        scaling calculations for you.
    */
    void GetPPIPrinter(int* w, int* h);

    /**
        Returns the number of pixels per logical inch of the screen device context.
        Dividing the printer PPI by the screen PPI can give a suitable scaling factor
        for drawing text onto the printer. If you are doing your own scaling, remember
        to multiply this by a scaling factor to take the preview DC size into account.
    */
    void GetPPIScreen(int* w, int* h);

    /**
        Called by the framework to obtain information from the application about minimum
        and maximum page values that the user can select, and the required page range to
        be printed. By default this returns 1, 32000 for the page minimum and maximum
        values, and 1, 1 for the required page range.
        If @a minPage is zero, the page number controls in the print dialog will be
        disabled.
    */
    void GetPageInfo(int* minPage, int* maxPage, int* pageFrom,
                     int* pageTo);

    /**
        Returns the size of the printer page in millimetres.
    */
    void GetPageSizeMM(int* w, int* h);

    /**
        Returns the size of the printer page in pixels, called the page rectangle.
        The page rectangle has a top left corner at (0,0) and a bottom right corner at
        (w,h). These values may not be the same as the values returned from
        wxDC::GetSize; if the printout is being used for
        previewing, a memory device context is used, which uses a bitmap size reflecting
        the current preview zoom. The application must take this discrepancy into
        account if previewing is to be supported.
    */
    void GetPageSizePixels(int* w, int* h);

    /**
        Returns the rectangle that corresponds to the entire paper in pixels, called the
        paper rectangle. This distinction between paper rectangle and page
        rectangle reflects the fact that most printers cannot print all the way to the
        edge of the paper. The page rectangle is a rectangle whose top left corner is at
        (0,0) and whose width and height are given by
        wxDC::GetPageSizePixels. On MSW and Mac,
        the page rectangle gives the printable area of the paper, while the paper
        rectangle represents the entire paper, including non-printable borders. Thus,
        the rectangle returned by GetPaperRectPixels will have a top left corner whose
        coordinates are small negative numbers and the bottom right corner will have
        values somewhat larger than the width and height given by
        wxDC::GetPageSizePixels. On other
        platforms and for PostScript printing, the paper is treated as if its entire
        area were printable, so this function will return the same rectangle as the page
        rectangle.
    */
    wxRect GetPaperRectPixels();

    /**
        Returns the title of the printout
    */
    wxString GetTitle();

    /**
        Should be overridden to return @true if the document has this page, or @false
        if not. Returning @false signifies the end of the document. By default,
        HasPage behaves as if the document has only one page.
    */
    bool HasPage(int pageNum);

    /**
        Returns @true if the printout is currently being used for previewing.
    */
    bool IsPreview();

    /**
        Set the user scale and device origin of the wxDC associated with this wxPrintout
        so that one screen pixel maps to one device pixel on the DC. That is, the user
        scale is set to (1,1) and the device origin is set to (0,0). Use this if you
        want to do your own scaling prior to calling wxDC drawing calls, for example, if
        your underlying model is floating-point and you want to achieve maximum drawing
        precision on high-resolution printers. (Note that while the underlying drawing
        model of Mac OS X is floating-point, wxWidgets's drawing model scales from
        integer
        coordinates.) You can use the GetLogicalXXXRect() routines below to obtain the
        paper rectangle, page rectangle, or page margins rectangle to perform your own
        scaling.
    */
    void MapScreenSizeToDevice();

    /**
        This sets the user scale of the wxDC assocated with this wxPrintout to the same
        scale as MapScreenSizeToPaper() but sets
        the logical origin to the top left corner of the page rectangle.
    */
    void MapScreenSizeToPage();

    /**
        This sets the user scale of the wxDC assocated with this wxPrintout to the same
        scale as
        MapScreenSizeToPageMargins() but
        sets the logical origin to the top left corner of the page margins specified by
        the given wxPageSetupDialogData object.
    */
    void MapScreenSizeToPageMargins(const wxPageSetupDialogData& pageSetupData);

    /**
        Set the user scale and device origin of the wxDC associated with this wxPrintout
        so that the printed page matches the screen size as closely as possible
        and the logical origin is in the top left corner of the paper rectangle.
        That is,
        a 100-pixel object on screen should appear at the same size on the printed
        page. (It
        will, of course, be larger or smaller in the preview image, depending on the
        zoom
        factor.) Use this if you want WYSIWYG behavior, e.g., in a text editor.
    */
    void MapScreenSizeToPaper();

    /**
        Shift the device origin by an amount specified in logical coordinates.
    */
    void OffsetLogicalOrigin(wxCoord xoff, wxCoord yoff);

    /**
        Called by the framework at the start of document printing. Return @false from
        this function cancels the print job. OnBeginDocument is called once for every
        copy printed.
        The base OnBeginDocument() @e must be called (and the return value
        checked) from within the overridden function, since it calls wxDC::StartDoc.
    */
    bool OnBeginDocument(int startPage, int endPage);

    /**
        Called by the framework at the start of printing. OnBeginPrinting is called
        once for every
        print job (regardless of how many copies are being printed).
    */
    void OnBeginPrinting();

    /**
        Called by the framework at the end of document printing. OnEndDocument
        is called once for every copy printed.
        The base OnEndDocument() @e must be called
        from within the overridden function, since it calls wxDC::EndDoc.
    */
    void OnEndDocument();

    /**
        Called by the framework at the end of printing. OnEndPrinting
        is called once for every print job (regardless of how many copies are being
        printed).
    */
    void OnEndPrinting();

    /**
        Called once by the framework before any other demands are made of the
        wxPrintout object. This gives the object an opportunity to calculate the
        number of pages in the document, for example.
    */
    void OnPreparePrinting();

    /**
        Called by the framework when a page should be printed. Returning @false cancels
        the print job. The application can use GetDC() to obtain a device
        context to draw on.
    */
    bool OnPrintPage(int pageNum);

    /**
        Set the device origin of the associated wxDC so that the current logical point
        becomes the new logical origin.
    */
    void SetLogicalOrigin(wxCoord x, wxCoord y);
};

