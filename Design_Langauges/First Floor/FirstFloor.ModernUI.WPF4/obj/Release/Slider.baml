   M S B A M L   `   `   `  ���� N  JFirstFloor.ModernUI, Version=1.0.9.0, Culture=neutral, PublicKeyToken=null[2clr-namespace:FirstFloor.ModernUI.Windows.Controls$FirstFloor.ModernUI.Windows.Controls  \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089   SliderRepeatButtonStyle  �� 
TargetType �� Property �� Value �� 
TargetType  BaseSliderThumbStyle  SliderThumbBackground  SliderThumbBorder �� Triggers P� Property P� Value  SliderThumbBackgroundHover  SliderThumbBorderHover ! SliderThumbBackgroundDragging  SliderThumbBorderDragging ! SliderThumbBackgroundDisabled 	 SliderThumbBorderDisabled 
 HorizontalSliderThumbStyle �� BasedOn  VerticalSliderThumbStyle J� SnapsToDevicePixels	 � RowDefinitions
 m�Name m� 	Placement  
SliderTick m� Fill ��Name  SliderTrackBorder  SliderTrackBackground ��Name  SliderSelectionBackground  SliderSelectionBorder ]� DecreaseRepeatButton �� DecreaseLarge ]� IncreaseRepeatButton �� IncreaseLarge ]� Thumb n�Name �� 
TargetName  SliderTickDisabled �� Triggers � ColumnDefinitions�� D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    :x,http://schemas.microsoft.com/winfx/2006/xaml     ?controls2clr-namespace:FirstFloor.ModernUI.Windows.Controls  %�  &	        &	 �     &	
 9    7  &	 w    7  '�� �    7   7   7 
 7   7   7  �� "  ��.���  �@�OverridesDefaultStyle . ��  � �� .  ��  � |� .  ��  � �� �� " ��.R��� 
������ �� "  n�.���  �@�OverridesDefaultStyle . ��  � |� .  ��  � �� .  ��  � ��# �  ��  � ��# �  ��  � ��$ 1q���  � �� �� " n�.R��� #��z��#��z��#��z�� P�  �@J�IsMouseOver . . ��� # �   � ���� # �   � ��P�  �@n�
IsDragging . . ��� # �   � ���� # �   � ��P�  � {� .  . ��� # �   � ���� # � 	  � ���� "  n�8   .���  � ��$ 22����  � ��$ 11���� "  n�8   .���  � ��$ 11����  � ��$ 22���� "  ��.���  �@�FocusVisualStyle Z� ��  �@��IsPressAndHoldEnabled .  ��  � ��
 ���� ��  � �� �� " ��.R��� #��z��#��z��#��z�� . ._�� 	 �� $
��Auto ��� $
��Auto �#��z���� $
��Auto �.+�m� $
 TopTick��$��0��$y�	Collapsed=�$	 Top=�# �  $��4��m� $
 
BottomTick��$��2��$y�	Collapsed=�$ Bottom=�# �  $��4���� $ TrackBackground��$��1��$	��5,0q�$��center=�#���  $��1q�#���  $	��4.0��._��� $��-6,-1q�.+��� $ PART_SelectionRange��#���  $	��4.0��$y�Hidden=�$	��1.0��#���  ]� $��
PART_Track��$��1�� �� 8��  #��Z  �� 8�� #��Z  n� $ Thumb��8��  P�  �@��TickPlacement$ TopLeft=�. ��� $ TopTick�� � y�$ Visible=��� $ TrackBackground�� � ��$ 5,2,5,0q�P�  �@��TickPlacement$ BottomRight=�. ��� $ 
BottomTick�� � y�$ Visible=��� $ TrackBackground�� � ��$ 5,0,5,2q�P�  �@��TickPlacement$
 Both=�. ��� $ TopTick�� � y�$ Visible=��� $ 
BottomTick�� � y�$ Visible=�P�  �@��IsSelectionRangeEnabled . . ��� $ PART_SelectionRange�� � y�$ Visible=�P�  � {� .  . ��� $ TopTick��# �   �@m�Fill�� $ 
BottomTick��# �   �@m�Fill P�  �@��Orientation$ Vertical=�. ���  � �� �� " ��.R��� #��z��#��z��#��z�� . ._��  �� $
��Auto ��� $
��Auto �#��z���� $
��Auto �.+�m� $
 TopTick��$��0��$y�	Collapsed=�$
 Left=�# �  $��4��m� $
 
BottomTick��$��2��$y�	Collapsed=�$ Right=�# �  $��4���� $��TrackBackground��$��1��$	��0,5q�$��center=�#���  $��1q�#���  $	��4.0��._��� $��-1,-6q�.+��� $ PART_SelectionRange��#���  $	��4.0��$y�Hidden=�$	��1.0��#���  ]� $��
PART_Track��$��1�� �� 8�� #��Z  �� 8�� #��Z  n� $ Thumb��8��  P�  �@��TickPlacement$ TopLeft=�. ��� $ TopTick�� � y�$ Visible=��� $ TrackBackground�� � ��$ 2,5,0,5q�P�  �@��TickPlacement$ BottomRight=�. ��� $ 
BottomTick�� � y�$ Visible=��� $ TrackBackground�� � ��$ 0,5,2,5q�P�  �@��TickPlacement$
 Both=�. ��� $ TopTick�� � y�$ Visible=��� $ 
BottomTick�� � y�$ Visible=�P�  �@��IsSelectionRangeEnabled . . ��� $ PART_SelectionRange�� � y�$ Visible=�P�  � {� .  . ��� $ TopTick��# �   �@m�Fill�� $ 
BottomTick��# �   �@m�Fill