/**
 * @file MachineDialog.cpp
 *
 * @author Anik Momtaz
 * @author Charles Owen
 *
 * You are not allowed to change this class in any way!
 */

#include "pch.h"

#include <wx/valnum.h>
#include <wx/stdpaths.h>

#include "IMachineSystem.h"

#include "MachineDialog.h"

/**
 * Constructor
 * @param parent Parent window to put this dialog box inside
 * @param machineSystem IMachineSystem we are editing
 */
MachineDialog::MachineDialog(wxWindow* parent, std::shared_ptr<IMachineSystem> machineSystem) :
    wxDialog(parent, wxID_ANY, L"Machine Selection"), mMachine(machineSystem)
{
    mMachineNumber = machineSystem->GetMachineNumber();

    this->SetSizeHints( wxDefaultSize, wxDefaultSize );

    wxBoxSizer* sizerMain;
    sizerMain = new wxBoxSizer( wxVERTICAL );

    // Where do the images come from?
    auto standardPaths = wxStandardPaths::Get();
    auto resourcesDir = standardPaths.GetResourcesDir().ToStdWstring();

    wxStaticBitmap* bitmap;
    bitmap = new wxStaticBitmap( this, wxID_ANY, wxBitmap( resourcesDir + "/images/machines.png", wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, 0 );
    sizerMain->Add( bitmap, 0, 0, 5 );

    wxBoxSizer* sizerHorz;
    sizerHorz = new wxBoxSizer( wxHORIZONTAL );

    wxStaticText* labelMachineNumber;
    labelMachineNumber = new wxStaticText( this, wxID_ANY, wxT("Machine Number:"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
    labelMachineNumber->Wrap( -1 );
    sizerHorz->Add( labelMachineNumber, 1, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxTOP, 10 );


    sizerHorz->Add( 5, 0, 0, wxEXPAND, 5 );

    mMachineNumberCtrl = new wxTextCtrl( this, wxID_ANY, wxT("1"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
    sizerHorz->Add( mMachineNumberCtrl, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxTOP, 10 );


    sizerMain->Add( sizerHorz, 1, wxALIGN_CENTER_HORIZONTAL, 5 );

    auto sizerButtons = new wxStdDialogButtonSizer();
    auto sizerButtonsOK = new wxButton( this, wxID_OK );
    sizerButtons->AddButton( sizerButtonsOK );
    auto sizerButtonsCancel = new wxButton( this, wxID_CANCEL );
    sizerButtons->AddButton( sizerButtonsCancel );
    sizerButtons->Realize();

    sizerMain->Add( sizerButtons, 1, wxALIGN_CENTER_HORIZONTAL, 5 );

    this->SetSizer( sizerMain );
    this->Layout();
    sizerMain->Fit( this );

    this->Centre( wxBOTH );

    wxIntegerValidator<int> validator(&mMachineNumber);
    mMachineNumberCtrl->SetValidator(validator);

    Bind(wxEVT_BUTTON, &MachineDialog::OnOK, this,wxID_OK);
    Bind(wxEVT_INIT_DIALOG, &MachineDialog::OnInitDialog, this);
}

/**
 * Handle the OK button press event
 * @param event Button press event
 */
void MachineDialog::OnOK([[maybe_unused]] wxCommandEvent& event)
{
    if ( Validate() && TransferDataFromWindow() )
    {
        EndModal(wxID_OK);
        mMachine->ChooseMachine(mMachineNumber);
    }
}

/**
 * Initialize dialog event handler.
 *
 * This allows us to preselect the content of the edit control
 * so we don't have to do so manually to change it.
 *
 * @param event EVT_INIT_DIALOG event object
 */
void MachineDialog::OnInitDialog([[maybe_unused]] wxInitDialogEvent& event)
{
    TransferDataToWindow();
    mMachineNumberCtrl->SelectAll();
}