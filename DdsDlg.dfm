object DdsDialog: TDdsDialog
  Left = 0
  Top = 0
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'DDS'
  ClientHeight = 241
  ClientWidth = 127
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
  object Label1: TLabel
    Left = 3
    Top = 32
    Width = 131
    Height = 15
    Caption = 'Frequency  (0 ~ 75MHz)'
  end
  object Label2: TLabel
    Left = 3
    Top = 77
    Width = 113
    Height = 15
    Caption = 'Amplitude (0 ~ 3.5V)'
  end
  object Label3: TLabel
    Left = 3
    Top = 123
    Width = 109
    Height = 15
    Caption = 'Offset         (-7 ~ 7V)'
  end
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
  object eFrq: TCurrencyEdit
    Left = 3
    Top = 48
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
  object cbFrq: TComboBox
    Left = 66
    Top = 48
    Width = 51
    Height = 23
    ItemHeight = 15
    ItemIndex = 1
    TabOrder = 2
    TabStop = False
    Text = 'kHZ'
    OnChange = DdsChange
    Items.Strings = (
      'Hz'
      'kHZ'
      'MHz')
  end
  object eAmpl: TCurrencyEdit
    Left = 3
    Top = 94
    Width = 63
    Height = 23
    Margins.Left = 4
    Margins.Top = 1
    TabStop = False
    DecimalPlaces = 3
    DisplayFormat = ',0.000;-,0.000'
    MaxValue = 3.500000000000000000
    TabOrder = 3
    Value = 1.000000000000000000
    OnChange = DdsChange
  end
  object eOffset: TCurrencyEdit
    Left = 3
    Top = 140
    Width = 63
    Height = 23
    Margins.Left = 4
    Margins.Top = 1
    TabStop = False
    DecimalPlaces = 3
    DisplayFormat = ',0.000;-,0.000'
    MaxValue = 7.000000000000000000
    MinValue = -7.000000000000000000
    TabOrder = 4
    OnChange = DdsChange
  end
  object FormStorage1: TFormStorage
    UseRegistry = False
    OnRestorePlacement = FormStorage1RestorePlacement
    StoredProps.Strings = (
      'eAmpl.Value'
      'eFrq.Value'
      'eOffset.Value'
      'cbFrq.ItemIndex'
      'cbDdsMode.ItemIndex')
    StoredValues = <>
    Left = 78
    Top = 1
  end
end
