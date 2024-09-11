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
        Width = 310
      end
      item
        Width = 50
      end
      item
        Width = 200
      end
      item
        Width = 100
      end>
  end
  object pDSO: TPanel
    Left = 0
    Top = 22
    Width = 462
    Height = 337
    Align = alClient
    Color = 14413534
    ParentBackground = False
    TabOrder = 1
    ExplicitTop = 0
    ExplicitHeight = 359
  end
  object panSwtch: TPanel
    Left = 605
    Top = 22
    Width = 16
    Height = 337
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
    ExplicitTop = 0
    ExplicitHeight = 359
  end
  object pTool: TPanel
    Left = 462
    Top = 22
    Width = 143
    Height = 337
    Align = alRight
    BevelOuter = bvNone
    TabOrder = 3
    ExplicitTop = 0
    ExplicitHeight = 359
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
        ItemHeight = 0
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
        ItemHeight = 0
        TabOrder = 1
        OnChange = TimeDivChange
      end
    end
    object gbChnl: TGroupBox
      Left = 0
      Top = 49
      Width = 143
      Height = 179
      Align = alClient
      Caption = '  Volts   '
      TabOrder = 1
      ExplicitHeight = 201
    end
    object gbTrgr: TGroupBox
      Left = 0
      Top = 294
      Width = 143
      Height = 43
      Align = alBottom
      Caption = '  Trigger  '
      TabOrder = 2
      ExplicitTop = 316
      object cbEdge: TComboBox
        Tag = 132
        Left = 78
        Top = 16
        Width = 60
        Height = 23
        ItemHeight = 0
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
        ItemHeight = 0
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
      Top = 228
      Width = 143
      Height = 66
      Align = alBottom
      TabOrder = 3
      ExplicitTop = 250
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
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 621
    Height = 22
    Align = alTop
    TabOrder = 4
    object bPause: TSpeedButton
      Tag = 101
      Left = 597
      Top = 1
      Width = 23
      Height = 20
      Align = alRight
      AllowAllUp = True
      GroupIndex = 240901
      Caption = 'II'
      OnClick = FBtnClick
      ExplicitLeft = 579
      ExplicitTop = 10
      ExplicitHeight = 22
    end
    object bDbg1: TSpeedButton
      Tag = 105
      Left = 561
      Top = 1
      Width = 36
      Height = 20
      Align = alRight
      AllowAllUp = True
      GroupIndex = 24090114
      Caption = 'dbg4'
      OnClick = FBtnClick
    end
    object SpeedButton1: TSpeedButton
      Tag = 102
      Left = 453
      Top = 1
      Width = 36
      Height = 20
      Align = alRight
      AllowAllUp = True
      GroupIndex = 24090111
      Caption = 'dbg1'
      OnClick = FBtnClick
      ExplicitLeft = 561
    end
    object SpeedButton2: TSpeedButton
      Tag = 103
      Left = 489
      Top = 1
      Width = 36
      Height = 20
      Align = alRight
      AllowAllUp = True
      GroupIndex = 24090112
      Caption = 'dbg2'
      OnClick = FBtnClick
      ExplicitLeft = 561
    end
    object SpeedButton3: TSpeedButton
      Tag = 104
      Left = 525
      Top = 1
      Width = 36
      Height = 20
      Align = alRight
      AllowAllUp = True
      GroupIndex = 24090113
      Caption = 'dbg3'
      OnClick = FBtnClick
      ExplicitLeft = 561
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
