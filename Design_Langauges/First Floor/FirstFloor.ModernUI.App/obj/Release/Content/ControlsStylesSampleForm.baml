   M S B A M L   `   `   `  ���� G  CModernUIDemo, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullA%clr-namespace:FirstFloor.ModernUI.AppFirstFloor.ModernUI.App  >    8FirstFloor.ModernUI.App.Content.ControlsStylesSampleForm   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     @d2http://schemas.microsoft.com/expression/blend/2008     N JFirstFloor.ModernUI, Version=1.0.9.0, Culture=neutral, PublicKeyToken=null0mui&http://firstfloorsoftware.com/ModernUI  /app%clr-namespace:FirstFloor.ModernUI.App  .���� .���� $	��200��.+��� $��SAMPLE FORM��   Heading2#��[  $��0,0,0,8q�6  0FirstFloor.ModernUI.Windows.Controls.BBCodeBlock      BBCode$g  aA sample form demonstrating various controls with support for validation and focus visualization.��$��0,0,0,16q��� -    ��Name$
 Form�� �� Orientation$ Vertical=� � DataContext 1   +FirstFloor.ModernUI.App.SampleFormViewModel   � 	Resources  �� 
TargetType �� Property �� Value �� BasedOn��%  '��       '�� R     7��'�� �     7��'	� �     7	��� " ��.���  �@��Orientation$ 
Horizontal=���  � ��$ 0,0,0,4q��� " ��8   .���  � ��$	 100����  � ��$ Center=��� " ��8   .���  � ��$	 0,3q��� " 	�8   .���  � ��$	 0,3q�.+��� .+��� $��
First name��	 �� Target	 �� 
 �� ElementName$
 TextFirstName���� -    ��Name$ TextFirstName��$	��150������ *	FirstName+ �� Mode$ TwoWay=� �� ValidatesOnDataErrors . �� .+��� $��	Last name��	 �� $
 TextLastName���� -   $ TextLastName��$	��150������ *
LastName+$ TwoWay=� . �� .+��� $��Gender��	 �� $
 RadioGendeMale��	� -    	�Name$ RadioGendeMale��.���� Male	� $��Female��$��8,0,0,0q��� .+��� $��
Birth date��	 �� $
 	DateBirth��(  "System.Windows.Controls.DatePicker  -     Name$ 	DateBirth���� .+��� $��Address��	 �� $
 TextAddress���� -   $ TextAddress��$	��150���� .+��� $
��City��	 �� $
 TextCity���� -   $ TextCity��$	��150���� .+��� $��State��	 �� $
 
ComboState���� -    ��Name$ 
ComboState��$	��150��.@��� .��	Alabama�� .��Alaska�� .��	Arizona�� .��
Arkansas�� .��
California�� .��
Colorado�� .��Connecticut�� .��
Delaware�� .��	Florida�� .��	Georgia�� .��Hawaii�� .��Idaho�� .��
Illinois�� .��	Indiana�� .��Iowa�� .��Kansas�� .��
Kentucky�� .��	Louisiana�� .��Maine�� .��
Maryland�� .��Massachusetts�� .��
Michigan�� .��	Minnesota�� .��Mississippi�� .��
Missouri�� .��	Montana�� .��
Nebraska�� .��Nevada�� .��New Hampshire�� .��
New Jersey�� .��
New Mexico�� .��
New York�� .��North Carolina�� .��North Dakota�� .��Ohio�� .��
Oklahoma�� .��Oregon�� .��Pennsylvania�� .��Rhode Island�� .��South Carolina�� .��South Dakota�� .��	Tennessee�� .��Texas�� .��Utah�� .��	Vermont�� .��
Virginia�� .��
Washington�� .��West Virginia�� .��	Wisconsin�� .��	Wyoming�� .+��� $��Zip code��	 �� $
 TextZipCode���� -	   $ TextZipCode��$	��150���� .+��� �� .���� $
��Bold"�I agree to the terms of use�� $��Submit��$��
100,16,0,0q�$
��Left=�