object FrmChnl: TFrmChnl
  Left = 0
  Top = 0
  Width = 130
  Height = 45
  TabOrder = 0
  OnResize = BtnOnClick
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 130
    Height = 45
    Align = alClient
    TabOrder = 0
    object bOn: TCheckBox
      Left = 3
      Top = 3
      Width = 51
      Height = 17
      TabStop = False
      Caption = 'CHNL'
      TabOrder = 0
      OnClick = BtnOnClick
    end
    object cbVoltDiv: TComboBox
      Left = 60
      Top = 1
      Width = 66
      Height = 21
      Hint = 'Volt/Div'
      Ctl3D = True
      ItemHeight = 0
      ParentCtl3D = False
      TabOrder = 2
      TabStop = False
      OnChange = BtnOnClick
    end
    object cbX10: TCheckBox
      Left = 3
      Top = 23
      Width = 51
      Height = 17
      TabStop = False
      Caption = 'x10'
      TabOrder = 1
      OnClick = BtnOnClick
    end
    object cbAC_DC: TComboBox
      Left = 60
      Top = 21
      Width = 66
      Height = 21
      Hint = 'DC/GND/AC'
      ItemHeight = 13
      TabOrder = 3
      TabStop = False
      OnChange = BtnOnClick
      Items.Strings = (
        'DC'
        'AC'
        'GND')
    end
  end
  object FormStorage1: TFormStorage
    Options = []
    UseRegistry = False
    OnRestorePlacement = FormStorage1RestorePlacement
    StoredProps.Strings = (
      'bOn.Checked'
      'cbX10.Checked'
      'cbVoltDiv.ItemIndex'
      'cbAC_DC.ItemIndex'
      'cbVoltDiv.Tag')
    StoredValues = <>
    Left = 15
    Top = 65532
  end
end
