object Form1: TForm1
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = 'DSO-6254 BD'
  ClientHeight = 358
  ClientWidth = 621
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Times New Roman'
  Font.Style = [fsBold]
  Menu = MainMenu1
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
    Top = 339
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
        Width = 200
      end>
  end
  object pDSO: TPanel
    Left = 0
    Top = 0
    Width = 472
    Height = 339
    Align = alClient
    Color = clMoneyGreen
    ParentBackground = False
    TabOrder = 1
  end
  object pcTool: TPageControl
    Left = 472
    Top = 0
    Width = 149
    Height = 339
    ActivePage = tsDSO
    Align = alRight
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    TabStop = False
    object tsDSO: TTabSheet
      Caption = 'DSO'
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object GroupBox1: TGroupBox
        Left = 0
        Top = 0
        Width = 141
        Height = 49
        Align = alTop
        Caption = '  Time   '
        TabOrder = 0
        object cbTimeDiv: TComboBox
          Left = 3
          Top = 20
          Width = 60
          Height = 23
          Hint = 'Sec/Div'
          ItemHeight = 0
          TabOrder = 0
        end
        object cbSmplDiv: TComboBox
          Left = 78
          Top = 20
          Width = 60
          Height = 23
          Hint = 'Smpl/Div'
          ItemHeight = 0
          TabOrder = 1
        end
      end
      object gbChnl: TGroupBox
        Left = 0
        Top = 49
        Width = 141
        Height = 217
        Align = alClient
        Caption = '  Volts   '
        TabOrder = 1
        ExplicitTop = 77
        ExplicitHeight = 94
      end
      object gbTrgr: TGroupBox
        Left = 0
        Top = 266
        Width = 141
        Height = 43
        Align = alBottom
        Caption = '  Trigger  '
        TabOrder = 2
        object cbEdge: TComboBox
          Left = 78
          Top = 16
          Width = 60
          Height = 23
          ItemHeight = 15
          TabOrder = 0
          Items.Strings = (
            'Rise'
            'Falling')
        end
        object cbSrcTrg: TComboBox
          Left = 3
          Top = 16
          Width = 60
          Height = 23
          Hint = 'Sec/Div'
          ItemHeight = 15
          TabOrder = 1
          Items.Strings = (
            'Off'
            'CH1'
            'CH2'
            'CH3'
            'CH4')
        end
      end
    end
    object tsDDS: TTabSheet
      Caption = 'DDS'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
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
        DisplayFormat = ',0.000;-,0.000'
        MaxValue = 999.000000000000000000
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
      'cbSrcTrg.ItemIndex')
    StoredValues = <>
    Left = 4
    Top = 1
  end
  object timRef: TTimer
    Interval = 10
    OnTimer = timRefTimer
    Left = 26
    Top = 2
  end
  object MainMenu1: TMainMenu
    Left = 41
    Top = 12
    object File1: TMenuItem
      Caption = '&File'
      object Save1: TMenuItem
        Caption = '&Save'
      end
    end
    object Edit1: TMenuItem
      Caption = '&Edit'
    end
  end
end
