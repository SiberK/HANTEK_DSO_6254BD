object Form1: TForm1
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = 'DSO-6254 BD'
  ClientHeight = 378
  ClientWidth = 621
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Times New Roman'
  Font.Style = [fsBold]
  OldCreateOrder = False
  ShowHint = True
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnMouseWheel = FormMouseWheel
  PixelsPerInch = 96
  TextHeight = 15
  object StatBar1: TStatusBar
    Left = 0
    Top = 359
    Width = 621
    Height = 19
    Panels = <
      item
        Bevel = pbNone
        Width = 150
      end
      item
        Width = 200
      end
      item
        Width = 120
      end
      item
        Width = 100
      end>
  end
  object pDSO: TPanel
    Left = 0
    Top = 0
    Width = 472
    Height = 359
    Align = alClient
    Color = clMoneyGreen
    ParentBackground = False
    TabOrder = 1
  end
  object pcTool: TPageControl
    Left = 472
    Top = 0
    Width = 149
    Height = 359
    ActivePage = tsDSO
    Align = alRight
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    TabStop = False
    object tsDSO: TTabSheet
      Caption = 'DSO'
      object GroupBox1: TGroupBox
        Left = 0
        Top = 0
        Width = 141
        Height = 49
        Align = alTop
        Caption = '  Time   '
        TabOrder = 0
        object cbTimeDiv: TComboBox
          Tag = 121
          Left = 3
          Top = 20
          Width = 60
          Height = 23
          Hint = 'Sec/Div'
          ItemHeight = 15
          TabOrder = 0
          OnChange = TimeDivChange
        end
        object cbSmplDiv: TComboBox
          Tag = 122
          Left = 78
          Top = 20
          Width = 60
          Height = 23
          Hint = 'Smpl/Div'
          ItemHeight = 15
          TabOrder = 1
          OnChange = TimeDivChange
        end
      end
      object gbChnl: TGroupBox
        Left = 0
        Top = 49
        Width = 141
        Height = 171
        Align = alClient
        Caption = '  Volts   '
        TabOrder = 1
      end
      object gbTrgr: TGroupBox
        Left = 0
        Top = 286
        Width = 141
        Height = 43
        Align = alBottom
        Caption = '  Trigger  '
        TabOrder = 2
        object cbEdge: TComboBox
          Tag = 132
          Left = 78
          Top = 16
          Width = 60
          Height = 23
          ItemHeight = 15
          TabOrder = 0
          OnChange = TimeDivChange
          Items.Strings = (
            'Rise'
            'Falling')
        end
        object cbSrcTrg: TComboBox
          Tag = 131
          Left = 3
          Top = 16
          Width = 60
          Height = 23
          Hint = 'Sec/Div'
          ItemHeight = 15
          TabOrder = 1
          OnChange = TimeDivChange
          Items.Strings = (
            'Off'
            'CH1'
            'CH2'
            'CH3'
            'CH4')
        end
      end
      object GroupBox2: TGroupBox
        Left = 0
        Top = 220
        Width = 141
        Height = 66
        Align = alBottom
        TabOrder = 3
        object eTimRef: TCurrencyEdit
          Left = 4
          Top = 12
          Width = 64
          Height = 23
          Margins.Left = 4
          Margins.Top = 1
          DecimalPlaces = 0
          DisplayFormat = ',0.00 mS;-,0.00 mS'
          MaxValue = 1000.000000000000000000
          MinValue = 10.000000000000000000
          TabOrder = 0
          Value = 10.000000000000000000
          OnChange = eTimRefChange
        end
      end
    end
    object tsDDS: TTabSheet
      Caption = 'DDS'
      ImageIndex = 1
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
        Left = 4
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
        Text = 'Off'
        OnChange = DDS_Change
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
        OnChange = DDS_Change
      end
      object cbFrq: TComboBox
        Left = 66
        Top = 48
        Width = 51
        Height = 23
        ItemHeight = 15
        ItemIndex = 2
        TabOrder = 2
        TabStop = False
        Text = 'MHz'
        OnChange = DDS_Change
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
        OnChange = DDS_Change
      end
      object eOffset: TCurrencyEdit
        Left = 4
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
        OnChange = DDS_Change
      end
    end
  end
  object FormStorage1: TFormStorage
    UseRegistry = False
    OnRestorePlacement = FormStorage1RestorePlacement
    StoredProps.Strings = (
      'eFrq.Value'
      'eAmpl.Value'
      'eOffset.Value'
      'cbFrq.ItemIndex'
      'cbTimeDiv.ItemIndex'
      'cbSmplDiv.ItemIndex'
      'cbEdge.ItemIndex'
      'cbSrcTrg.ItemIndex'
      'pDSO.Tag')
    StoredValues = <>
    Left = 4
    Top = 1
  end
  object timRef: TTimer
    Enabled = False
    Interval = 100
    OnTimer = timRefTimer
    Left = 26
    Top = 2
  end
end
