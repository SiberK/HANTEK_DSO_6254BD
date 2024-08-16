object FrmDSO: TFrmDSO
  Left = 0
  Top = 0
  Width = 425
  Height = 335
  Ctl3D = False
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'GOST type A'
  Font.Style = [fsBold]
  ParentCtl3D = False
  ParentFont = False
  TabOrder = 0
  OnMouseDown = FrameMouseDown
  OnMouseWheel = FrameMouseWheel
  object Label2: TLabel
    Left = 277
    Top = 101
    Width = 40
    Height = 17
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
    OnMouseMove = FMouseMove
    OnResize = pViewResize
    object Label1: TLabel
      Left = 180
      Top = 143
      Width = 32
      Height = 14
      Caption = 'Label1'
      Color = clGradientActiveCaption
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'GOST type A'
      Font.Style = [fsBold]
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
    Color = clMoneyGreen
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clBlue
    Font.Height = -13
    Font.Name = 'GOST type A'
    Font.Style = [fsBold]
    ParentBackground = False
    ParentFont = False
    TabOrder = 1
  end
  object pRight: TPanel
    Left = 409
    Top = 16
    Width = 16
    Height = 303
    Align = alRight
    BevelOuter = bvNone
    Color = clMoneyGreen
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'GOST type A'
    Font.Style = [fsBold]
    ParentBackground = False
    ParentFont = False
    TabOrder = 2
  end
  object pTop2: TPanel
    Left = 0
    Top = 0
    Width = 425
    Height = 16
    Align = alTop
    BevelOuter = bvNone
    Color = clMoneyGreen
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'GOST type A'
    Font.Style = [fsBold]
    ParentBackground = False
    ParentFont = False
    TabOrder = 3
    OnResize = PanResize
    object btn2: TSpeedButton
      Tag = 12
      Left = 409
      Top = 0
      Width = 16
      Height = 16
      Align = alRight
      AllowAllUp = True
      GroupIndex = 12
      ExplicitLeft = 410
    end
    object btn1: TSpeedButton
      Tag = 11
      Left = 0
      Top = 0
      Width = 16
      Height = 16
      Align = alLeft
      AllowAllUp = True
      GroupIndex = 11
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
    end
  end
  object pBottom2: TPanel
    Left = 0
    Top = 319
    Width = 425
    Height = 16
    Align = alBottom
    BevelOuter = bvNone
    Color = clMoneyGreen
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'GOST type A'
    Font.Style = [fsBold]
    ParentBackground = False
    ParentFont = False
    TabOrder = 4
    OnResize = PanResize
    object btn3: TSpeedButton
      Tag = 13
      Left = 409
      Top = 0
      Width = 16
      Height = 16
      Align = alRight
      AllowAllUp = True
      GroupIndex = 13
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
    end
    object pBottom: TPanel
      Left = 16
      Top = 0
      Width = 393
      Height = 16
      Align = alClient
      BevelOuter = bvNone
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clBlack
      Font.Height = -16
      Font.Name = 'Calibri'
      Font.Style = [fsBold]
      ParentColor = True
      ParentFont = False
      TabOrder = 0
    end
  end
  object FormStorage1: TFormStorage
    Options = []
    UseRegistry = False
    StoredProps.Strings = (
      'pLeft.Tag'
      'pRight.Tag'
      'pTop2.Tag'
      'pBottom2.Tag')
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
      OnClick = On1Click
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
end
