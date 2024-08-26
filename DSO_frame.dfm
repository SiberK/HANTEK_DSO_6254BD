object FrmDSO: TFrmDSO
  Left = 0
  Top = 0
  Width = 425
  Height = 335
  Ctl3D = False
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Calibri'
  Font.Style = [fsBold]
  ParentCtl3D = False
  ParentFont = False
  TabOrder = 0
  OnMouseDown = FMouseDown
  OnMouseWheel = FMouseWheel
  object Label2: TLabel
    Left = 277
    Top = 101
    Width = 44
    Height = 19
    Caption = 'Label2'
  end
  object pView: TScrollBox
    Left = 16
    Top = 16
    Width = 393
    Height = 303
    HorzScrollBar.Visible = False
    VertScrollBar.Visible = False
    Align = alClient
    BevelInner = bvNone
    BevelOuter = bvNone
    Color = clHighlight
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'GOST type A'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 0
    OnMouseDown = FMouseDown
    OnMouseMove = FMouseMove
    OnMouseUp = FMouseUp
    OnResize = FResize
    object Label1: TLabel
      Left = 180
      Top = 143
      Width = 26
      Height = 14
      Caption = 'Label1'
      Color = clGradientActiveCaption
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'GOST type A'
      Font.Style = []
      ParentColor = False
      ParentFont = False
      Transparent = False
    end
  end
  object pLeft: TPanel
    Left = 0
    Top = 16
    Width = 16
    Height = 303
    Align = alLeft
    BevelOuter = bvNone
    ParentBackground = False
    ParentColor = True
    TabOrder = 1
  end
  object pRight: TPanel
    Left = 409
    Top = 16
    Width = 16
    Height = 303
    Align = alRight
    BevelOuter = bvNone
    ParentBackground = False
    ParentColor = True
    TabOrder = 2
  end
  object pTop2: TPanel
    Left = 0
    Top = 0
    Width = 425
    Height = 16
    Align = alTop
    BevelOuter = bvNone
    ParentBackground = False
    ParentColor = True
    TabOrder = 3
    object bStretch: TSpeedButton
      Tag = 12
      Left = 409
      Top = 0
      Width = 16
      Height = 16
      Hint = #1056#1072#1089#1090#1103#1078#1082#1072' x0.1'
      Align = alRight
      AllowAllUp = True
      GroupIndex = 12
      OnClick = BtnClick
      ExplicitLeft = 410
    end
    object bFixTrgT: TSpeedButton
      Tag = 11
      Left = 0
      Top = 0
      Width = 16
      Height = 16
      Hint = #1092#1080#1082#1089'. TrgT'
      Align = alLeft
      AllowAllUp = True
      GroupIndex = 11
      OnClick = BtnClick
    end
    object pTop: TPanel
      Left = 16
      Top = 0
      Width = 393
      Height = 16
      Align = alClient
      BevelOuter = bvNone
      ParentColor = True
      TabOrder = 0
      object lblTrgT: TLabel
        Left = 363
        Top = 0
        Width = 30
        Height = 16
        Align = alRight
        Alignment = taCenter
        AutoSize = False
        Caption = 'lblTrgT'
        ExplicitLeft = 347
      end
      object shpView: TShape
        Left = 54
        Top = 1
        Width = 65
        Height = 14
        Brush.Style = bsClear
        OnMouseMove = FMouseMove
      end
    end
  end
  object pBottom2: TPanel
    Left = 0
    Top = 319
    Width = 425
    Height = 16
    Align = alBottom
    BevelOuter = bvNone
    ParentBackground = False
    ParentColor = True
    TabOrder = 4
    object btn3: TSpeedButton
      Tag = 13
      Left = 409
      Top = 0
      Width = 16
      Height = 16
      Hint = 'DDS'
      Align = alRight
      AllowAllUp = True
      GroupIndex = 13
      Caption = 'DDS'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clBlack
      Font.Height = -8
      Font.Name = 'GOST type A'
      Font.Style = [fsBold]
      ParentFont = False
      OnClick = BtnClick
      ExplicitLeft = 410
    end
    object btn4: TSpeedButton
      Tag = 14
      Left = 0
      Top = 0
      Width = 16
      Height = 16
      Align = alLeft
      AllowAllUp = True
      GroupIndex = 14
      OnClick = BtnClick
    end
    object pBottom: TPanel
      Left = 16
      Top = 0
      Width = 393
      Height = 16
      Align = alClient
      BevelOuter = bvNone
      ParentColor = True
      TabOrder = 0
      object lblTimDiv: TLabel
        Left = 343
        Top = 0
        Width = 50
        Height = 16
        Align = alRight
        AutoSize = False
        Caption = 'lblTimDiv'
        ExplicitLeft = 337
        ExplicitTop = 6
      end
    end
  end
  object FormStorage1: TFormStorage
    Options = []
    UseRegistry = False
    StoredProps.Strings = (
      'pLeft.Tag'
      'pRight.Tag'
      'pBottom.Tag'
      'pTop.Tag'
      'miALT.Checked'
      'miAUTO.Checked'
      'miCAN.Checked'
      'miCH1.Checked'
      'miCH2.Checked'
      'miCH3.Checked'
      'miCH4.Checked'
      'miEdge.Checked'
      'miFalling.Checked'
      'miI2C.Checked'
      'miLin.Checked'
      'miNORMAL.Checked'
      'miPulse.Checked'
      'miRising.Checked'
      'miSINGLE.Checked'
      'miSPI.Checked'
      'miUART.Checked'
      'miVideo.Checked'
      'miMode.Tag'
      'miSlope.Tag'
      'miSource.Tag'
      'miSweep.Tag')
    StoredValues = <>
    Left = 30
    Top = 29
  end
  object pmChnl: TPopupMenu
    Left = 61
    Top = 36
    object On1: TMenuItem
      AutoCheck = True
      Caption = 'On'
    end
    object VDiv1: TMenuItem
      Caption = 'V/Div'
      object N20mV1: TMenuItem
        Caption = '2.0mV'
      end
      object N50mV1: TMenuItem
        Caption = '5.0mV'
      end
    end
    object Couple1: TMenuItem
      Caption = 'Couple'
      object DC1: TMenuItem
        Caption = 'DC'
      end
      object AC1: TMenuItem
        Caption = 'AC'
      end
      object GND1: TMenuItem
        Caption = 'GND'
      end
    end
  end
  object popTrgV: TPopupMenu
    Left = 61
    Top = 74
    object miMode: TMenuItem
      Caption = 'Mode'
      object miEdge: TMenuItem
        Tag = 11
        AutoCheck = True
        Caption = 'Edge'
        GroupIndex = 10
        RadioItem = True
        OnClick = popTrgClick
      end
      object miPulse: TMenuItem
        Tag = 12
        AutoCheck = True
        Caption = 'Pulse'
        GroupIndex = 10
        RadioItem = True
        OnClick = popTrgClick
      end
      object miVideo: TMenuItem
        Tag = 13
        AutoCheck = True
        Caption = 'Video'
        GroupIndex = 10
        RadioItem = True
        Visible = False
        OnClick = popTrgClick
      end
      object miCAN: TMenuItem
        Tag = 14
        AutoCheck = True
        Caption = 'CAN'
        GroupIndex = 10
        RadioItem = True
        Visible = False
        OnClick = popTrgClick
      end
      object miLin: TMenuItem
        Tag = 15
        AutoCheck = True
        Caption = 'LIN'
        GroupIndex = 10
        RadioItem = True
        Visible = False
        OnClick = popTrgClick
      end
      object miUART: TMenuItem
        Tag = 16
        AutoCheck = True
        Caption = 'UART'
        GroupIndex = 10
        RadioItem = True
        Visible = False
        OnClick = popTrgClick
      end
      object miSPI: TMenuItem
        Tag = 17
        AutoCheck = True
        Caption = 'SPI'
        GroupIndex = 10
        RadioItem = True
        Visible = False
        OnClick = popTrgClick
      end
      object miI2C: TMenuItem
        Tag = 18
        AutoCheck = True
        Caption = 'I2C'
        GroupIndex = 10
        RadioItem = True
        Visible = False
        OnClick = popTrgClick
      end
      object miALT: TMenuItem
        Tag = 19
        AutoCheck = True
        Caption = 'ALT'
        GroupIndex = 10
        RadioItem = True
        Visible = False
        OnClick = popTrgClick
      end
    end
    object miSweep: TMenuItem
      Caption = 'Sweep'
      object miAUTO: TMenuItem
        Tag = 21
        AutoCheck = True
        Caption = 'AUTO'
        GroupIndex = 20
        RadioItem = True
        OnClick = popTrgClick
      end
      object miNORMAL: TMenuItem
        Tag = 22
        AutoCheck = True
        Caption = 'NORMAL'
        GroupIndex = 20
        RadioItem = True
        OnClick = popTrgClick
      end
      object miSINGLE: TMenuItem
        Tag = 23
        AutoCheck = True
        Caption = 'SINGLE'
        GroupIndex = 20
        RadioItem = True
        OnClick = popTrgClick
      end
    end
    object miSource: TMenuItem
      Caption = 'Source'
      object miCH1: TMenuItem
        Tag = 31
        AutoCheck = True
        Caption = 'CH1'
        RadioItem = True
        OnClick = popTrgClick
      end
      object miCH2: TMenuItem
        Tag = 32
        AutoCheck = True
        Caption = 'CH2'
        RadioItem = True
        OnClick = popTrgClick
      end
      object miCH3: TMenuItem
        Tag = 33
        AutoCheck = True
        Caption = 'CH3'
        RadioItem = True
        OnClick = popTrgClick
      end
      object miCH4: TMenuItem
        Tag = 34
        AutoCheck = True
        Caption = 'CH4'
        RadioItem = True
        OnClick = popTrgClick
      end
    end
    object miSlope: TMenuItem
      Caption = 'Slope'
      object miRising: TMenuItem
        Tag = 41
        AutoCheck = True
        Caption = '/'
        RadioItem = True
        OnClick = popTrgClick
      end
      object miFalling: TMenuItem
        Tag = 42
        AutoCheck = True
        Caption = '\'
        RadioItem = True
        OnClick = popTrgClick
      end
    end
  end
end
