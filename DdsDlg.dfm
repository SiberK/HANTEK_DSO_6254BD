object DdsDialog: TDdsDialog
  Left = 0
  Top = 0
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'DDS'
  ClientHeight = 399
  ClientWidth = 132
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Times New Roman'
  Font.Style = [fsBold]
  OldCreateOrder = False
  OnDestroy = FormDestroy
  OnMouseWheel = FormMouseWheel
  PixelsPerInch = 96
  TextHeight = 15
  object pFrq: TPanel
    Left = 0
    Top = 28
    Width = 132
    Height = 46
    Align = alTop
    Alignment = taLeftJustify
    BevelOuter = bvNone
    Caption = 'Frequency  (0 ~ 75MHz)'
    TabOrder = 0
    VerticalAlignment = taAlignTop
    object cbFrq: TComboBox
      Left = 67
      Top = 18
      Width = 51
      Height = 23
      ItemHeight = 15
      ItemIndex = 1
      TabOrder = 0
      TabStop = False
      Text = 'kHZ'
      OnChange = DdsChange
      Items.Strings = (
        'Hz'
        'kHZ'
        'MHz')
    end
    object eFrq: TCurrencyEdit
      Left = 3
      Top = 18
      Width = 63
      Height = 23
      Margins.Left = 4
      Margins.Top = 1
      TabStop = False
      DecimalPlaces = 3
      DisplayFormat = ',0.0;-,0.0'
      MaxValue = 1000.000000000000000000
      MinValue = 1.000000000000000000
      TabOrder = 1
      Value = 1.000000000000000000
      OnChange = DdsChange
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 132
    Height = 28
    Align = alTop
    Alignment = taLeftJustify
    BevelOuter = bvNone
    TabOrder = 1
    VerticalAlignment = taAlignTop
    object cbDdsMode: TComboBox
      Left = 3
      Top = 3
      Width = 67
      Height = 23
      ItemHeight = 15
      ItemIndex = 0
      TabOrder = 0
      TabStop = False
      Text = 'Off'
      OnChange = DdsChange
      Items.Strings = (
        'Off'
        'Sine'
        'Square'
        'Ramp'
        'Trapezia'
        'Arb'
        'Exponent'
        'AM/FM'
        'Gause'
        'White')
    end
  end
  object pOfst: TPanel
    Left = 0
    Top = 120
    Width = 132
    Height = 46
    Align = alTop
    Alignment = taLeftJustify
    BevelOuter = bvNone
    Caption = 'Offset         (-7 ~ 7V)'
    TabOrder = 2
    VerticalAlignment = taAlignTop
    object eOffset: TCurrencyEdit
      Left = 3
      Top = 18
      Width = 63
      Height = 23
      Margins.Left = 4
      Margins.Top = 1
      TabStop = False
      DecimalPlaces = 3
      DisplayFormat = ',0.000;-,0.000'
      MaxValue = 7.000000000000000000
      MinValue = -7.000000000000000000
      TabOrder = 0
      OnChange = DdsChange
    end
  end
  object pPhase: TPanel
    Left = 0
    Top = 166
    Width = 132
    Height = 46
    Align = alTop
    Alignment = taLeftJustify
    BevelOuter = bvNone
    Caption = 'Phase             Duty'
    TabOrder = 3
    VerticalAlignment = taAlignTop
    object ePhase: TCurrencyEdit
      Left = 3
      Top = 18
      Width = 60
      Height = 23
      Margins.Left = 4
      Margins.Top = 1
      TabStop = False
      DisplayFormat = ',0.00;-,0.00'
      MaxValue = 1.000000000000000000
      TabOrder = 0
      OnChange = DdsChange
    end
    object eDuty: TCurrencyEdit
      Left = 69
      Top = 18
      Width = 60
      Height = 23
      Margins.Left = 4
      Margins.Top = 1
      TabStop = False
      DisplayFormat = ',0.00;-,0.00'
      MaxValue = 1.000000000000000000
      TabOrder = 1
      Value = 0.500000000000000000
      OnChange = DdsChange
    end
  end
  object pAmpl: TPanel
    Left = 0
    Top = 74
    Width = 132
    Height = 46
    Align = alTop
    Alignment = taLeftJustify
    BevelOuter = bvNone
    Caption = 'Amplitude (0 ~ 3.5V)'
    TabOrder = 4
    VerticalAlignment = taAlignTop
    object eAmpl: TCurrencyEdit
      Left = 3
      Top = 18
      Width = 63
      Height = 23
      Margins.Left = 4
      Margins.Top = 1
      TabStop = False
      DecimalPlaces = 3
      DisplayFormat = ',0.000;-,0.000'
      MaxValue = 3.500000000000000000
      TabOrder = 0
      Value = 1.000000000000000000
      OnChange = DdsChange
    end
  end
  object pAMFM: TPanel
    Left = 0
    Top = 299
    Width = 132
    Height = 100
    Align = alBottom
    Alignment = taLeftJustify
    BevelOuter = bvNone
    Caption = 'CW Frequency'
    TabOrder = 5
    VerticalAlignment = taAlignTop
    object Label1: TLabel
      Left = 57
      Top = 50
      Width = 32
      Height = 15
      Caption = 'Depth'
    end
    object Label2: TLabel
      Left = 3
      Top = 77
      Width = 53
      Height = 15
      Caption = 'Freq. Dev.'
    end
    object Label3: TLabel
      Left = 105
      Top = 77
      Width = 23
      Height = 15
      Caption = 'kHz'
    end
    object eCWFrq: TCurrencyEdit
      Left = 3
      Top = 18
      Width = 63
      Height = 23
      Margins.Left = 4
      Margins.Top = 1
      TabStop = False
      DecimalPlaces = 3
      DisplayFormat = ',0.0;-,0.0'
      MaxValue = 1000.000000000000000000
      MinValue = 1.000000000000000000
      TabOrder = 0
      Value = 1.000000000000000000
      OnChange = DdsChange
    end
    object cbCWFrq: TComboBox
      Left = 67
      Top = 18
      Width = 51
      Height = 23
      ItemHeight = 15
      ItemIndex = 1
      TabOrder = 1
      TabStop = False
      Text = 'kHZ'
      OnChange = DdsChange
      Items.Strings = (
        'Hz'
        'kHZ'
        'MHz')
    end
    object eAMDepth: TCurrencyEdit
      Left = 95
      Top = 43
      Width = 34
      Height = 23
      Margins.Left = 4
      Margins.Top = 1
      TabStop = False
      DisplayFormat = ',0.00;-,0.00'
      MaxValue = 1.000000000000000000
      TabOrder = 2
      Value = 0.200000000000000000
      OnChange = DdsChange
    end
    object cbFM: TCheckBox
      Left = 3
      Top = 50
      Width = 40
      Height = 17
      Caption = 'FM'
      TabOrder = 3
    end
    object eFMDev: TCurrencyEdit
      Left = 60
      Top = 70
      Width = 43
      Height = 23
      Margins.Left = 4
      Margins.Top = 1
      TabStop = False
      DecimalPlaces = 0
      DisplayFormat = ',0;-,0'
      MaxValue = 1000.000000000000000000
      MinValue = 1.000000000000000000
      TabOrder = 4
      Value = 300.000000000000000000
      OnChange = DdsChange
    end
  end
  object pRise: TPanel
    Left = 0
    Top = 212
    Width = 132
    Height = 46
    Align = alTop
    Alignment = taLeftJustify
    BevelOuter = bvNone
    Caption = '   Rise     High      Fall'
    TabOrder = 6
    VerticalAlignment = taAlignTop
    object eRise: TCurrencyEdit
      Left = 3
      Top = 18
      Width = 40
      Height = 23
      Margins.Left = 4
      Margins.Top = 1
      TabStop = False
      DisplayFormat = ',0.00;-,0.00'
      MaxValue = 1.000000000000000000
      TabOrder = 0
      Value = 0.200000000000000000
      OnChange = DdsChange
    end
    object eHigh: TCurrencyEdit
      Left = 46
      Top = 18
      Width = 40
      Height = 23
      Margins.Left = 4
      Margins.Top = 1
      TabStop = False
      DisplayFormat = ',0.00;-,0.00'
      MaxValue = 1.000000000000000000
      TabOrder = 1
      Value = 0.400000000000000000
      OnChange = DdsChange
    end
    object eFall: TCurrencyEdit
      Left = 89
      Top = 18
      Width = 40
      Height = 23
      Margins.Left = 4
      Margins.Top = 1
      TabStop = False
      DisplayFormat = ',0.00;-,0.00'
      MaxValue = 1.000000000000000000
      TabOrder = 2
      Value = 0.200000000000000000
      OnChange = DdsChange
    end
  end
  object FormStorage1: TFormStorage
    UseRegistry = False
    OnRestorePlacement = FormStorage1RestorePlacement
    StoredProps.Strings = (
      'eAmpl.Value'
      'eFrq.Value'
      'eOffset.Value'
      'cbFrq.ItemIndex'
      'cbDdsMode.ItemIndex'
      'eDuty.Value'
      'eFall.Value'
      'eHigh.Value'
      'ePhase.Value'
      'eRise.Value'
      'cbCWFrq.ItemIndex'
      'cbFM.Checked'
      'eCWFrq.Value'
      'eFMDev.Value'
      'eAMDepth.Value')
    StoredValues = <>
    Left = 78
    Top = 1
  end
end
