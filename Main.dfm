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
        Width = 260
      end
      item
        Width = 120
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
    Width = 462
    Height = 359
    Align = alClient
    Color = 14413534
    ParentBackground = False
    TabOrder = 1
  end
  object panSwtch: TPanel
    Left = 605
    Top = 0
    Width = 16
    Height = 359
    Align = alRight
    BevelOuter = bvNone
    Caption = '<'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Times New Roman'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnDblClick = PanDblClick
  end
  object pTool: TPanel
    Left = 462
    Top = 0
    Width = 143
    Height = 359
    Align = alRight
    BevelOuter = bvNone
    TabOrder = 3
    object GroupBox1: TGroupBox
      Left = 0
      Top = 0
      Width = 143
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
      Width = 143
      Height = 201
      Align = alClient
      Caption = '  Volts   '
      TabOrder = 1
    end
    object gbTrgr: TGroupBox
      Left = 0
      Top = 316
      Width = 143
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
      Top = 250
      Width = 143
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
  object FormStorage1: TFormStorage
    UseRegistry = False
    OnRestorePlacement = FormStorage1RestorePlacement
    StoredProps.Strings = (
      'cbTimeDiv.ItemIndex'
      'cbSmplDiv.ItemIndex'
      'cbEdge.ItemIndex'
      'cbSrcTrg.ItemIndex'
      'pDSO.Tag'
      'pTool.Visible')
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
