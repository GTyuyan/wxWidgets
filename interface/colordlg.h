/////////////////////////////////////////////////////////////////////////////
// Name:        colordlg.h
// Purpose:     interface of wxColourDialog
// Author:      wxWidgets team
// RCS-ID:      $Id$
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

/**
    @class wxColourDialog
    @wxheader{colordlg.h}

    This class represents the colour chooser dialog.

    @library{wxcore}
    @category{cmndlg}

    @see @ref overview_wxcolourdialogoverview "wxColourDialog Overview", wxColour,
    wxColourData, wxGetColourFromUser()
*/
class wxColourDialog : public wxDialog
{
public:
    /**
        Constructor. Pass a parent window, and optionally a pointer to a block of colour
        data, which will be copied to the colour dialog's colour data. Custom
        colours from colour data object will be be used in dialog's colour palette.
        Invalid entries in custom colours list will be ignored on some platforms (GTK)
        or replaced with white colour on platforms where custom colours palette has
        fixed size (MSW).

        @see wxColourData
    */
    wxColourDialog(wxWindow* parent, wxColourData* data = NULL);

    /**
        Destructor.
    */
    ~wxColourDialog();

    /**
        Same as @ref ctor() constructor.
    */
    bool Create(wxWindow* parent, wxColourData* data = NULL);

    /**
        Returns the @ref overview_wxcolourdata "colour data" associated with the colour
        dialog.
    */
    wxColourData GetColourData();

    /**
        Shows the dialog, returning wxID_OK if the user pressed OK, and wxID_CANCEL
        otherwise.
    */
    int ShowModal();
};



// ============================================================================
// Global functions/macros
// ============================================================================

/** @ingroup group_funcmacro_dialog */
//@{

/**
    Shows the colour selection dialog and returns the colour selected by user
    or invalid colour (use wxColour::IsOk() to test whether a colour is valid)
    if the dialog was cancelled.

    @param parent
        The parent window for the colour selection dialog.
    @param colInit
        If given, this will be the colour initially selected in the dialog.
    @param caption
        If given, this will be used for the dialog caption.
    @param data
        Optional object storing additional colour dialog settings, such as
        custom colours. If none is provided the same settings as the last time
        are used.

    @header{wx/colordlg.h}
*/
wxColour wxGetColourFromUser(wxWindow* parent,
                             const wxColour& colInit,
                             const wxString& caption = wxEmptyString,
                             wxColourData* data = NULL);

//@}

