object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 299
  ClientWidth = 635
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Times New Roman'
  Font.Style = [fsBold]
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 15
  object Panel1: TPanel
    Left = 0
    Top = 253
    Width = 635
    Height = 27
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitTop = 272
    object bInit: TSpeedButton
      Left = 2
      Top = 2
      Width = 22
      Height = 22
    end
    object SpeedButton1: TSpeedButton
      Left = 30
      Top = 2
      Width = 22
      Height = 22
    end
  end
  object StatBar1: TStatusBar
    Left = 0
    Top = 280
    Width = 635
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
    ExplicitTop = 283
  end
  object pDSO: TPanel
    Left = 0
    Top = 0
    Width = 635
    Height = 253
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 2
    ExplicitTop = -4
  end
  object FormStorage1: TFormStorage
    UseRegistry = False
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
end
