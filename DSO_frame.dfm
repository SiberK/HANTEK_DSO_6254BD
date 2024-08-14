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
  object Label2: TLabel
    Left = 277
    Top = 101
    Width = 40
    Height = 17
    Caption = 'Label2'
  end
  object pView: TScrollBox
    Left = 15
    Top = 16
    Width = 395
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
    ExplicitTop = 19
    ExplicitHeight = 296
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
    Width = 15
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
    OnResize = PanResize
    ExplicitTop = 19
    ExplicitHeight = 296
  end
  object pRight: TPanel
    Left = 410
    Top = 16
    Width = 15
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
    OnResize = PanResize
    ExplicitTop = 19
    ExplicitHeight = 296
  end
  object pTop: TPanel
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
  end
  object pBottom: TPanel
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
  end
  object FormStorage1: TFormStorage
    Options = []
    UseRegistry = False
    StoredProps.Strings = (
      'pLeft.Tag'
      'pRight.Tag'
      'pTop.Tag'
      'pBottom.Tag')
    StoredValues = <>
    Left = 30
    Top = 29
  end
end
