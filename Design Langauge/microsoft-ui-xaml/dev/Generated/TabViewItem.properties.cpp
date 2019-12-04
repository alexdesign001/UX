// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

// DO NOT EDIT! This file was generated by CustomTasks.DependencyPropertyCodeGen
#include "pch.h"
#include "common.h"
#include "TabViewItem.h"

CppWinRTActivatableClassWithDPFactory(TabViewItem)

GlobalDependencyProperty TabViewItemProperties::s_HeaderProperty{ nullptr };
GlobalDependencyProperty TabViewItemProperties::s_HeaderTemplateProperty{ nullptr };
GlobalDependencyProperty TabViewItemProperties::s_IconSourceProperty{ nullptr };
GlobalDependencyProperty TabViewItemProperties::s_IsClosableProperty{ nullptr };
GlobalDependencyProperty TabViewItemProperties::s_TabViewTemplateSettingsProperty{ nullptr };

TabViewItemProperties::TabViewItemProperties()
    : m_closeRequestedEventSource{static_cast<TabViewItem*>(this)}
{
    EnsureProperties();
}

void TabViewItemProperties::EnsureProperties()
{
    if (!s_HeaderProperty)
    {
        s_HeaderProperty =
            InitializeDependencyProperty(
                L"Header",
                winrt::name_of<winrt::IInspectable>(),
                winrt::name_of<winrt::TabViewItem>(),
                false /* isAttached */,
                ValueHelper<winrt::IInspectable>::BoxedDefaultValue(),
                winrt::PropertyChangedCallback(&OnHeaderPropertyChanged));
    }
    if (!s_HeaderTemplateProperty)
    {
        s_HeaderTemplateProperty =
            InitializeDependencyProperty(
                L"HeaderTemplate",
                winrt::name_of<winrt::DataTemplate>(),
                winrt::name_of<winrt::TabViewItem>(),
                false /* isAttached */,
                ValueHelper<winrt::DataTemplate>::BoxedDefaultValue(),
                nullptr);
    }
    if (!s_IconSourceProperty)
    {
        s_IconSourceProperty =
            InitializeDependencyProperty(
                L"IconSource",
                winrt::name_of<winrt::IconSource>(),
                winrt::name_of<winrt::TabViewItem>(),
                false /* isAttached */,
                ValueHelper<winrt::IconSource>::BoxedDefaultValue(),
                winrt::PropertyChangedCallback(&OnIconSourcePropertyChanged));
    }
    if (!s_IsClosableProperty)
    {
        s_IsClosableProperty =
            InitializeDependencyProperty(
                L"IsClosable",
                winrt::name_of<bool>(),
                winrt::name_of<winrt::TabViewItem>(),
                false /* isAttached */,
                ValueHelper<bool>::BoxValueIfNecessary(true),
                winrt::PropertyChangedCallback(&OnIsClosablePropertyChanged));
    }
    if (!s_TabViewTemplateSettingsProperty)
    {
        s_TabViewTemplateSettingsProperty =
            InitializeDependencyProperty(
                L"TabViewTemplateSettings",
                winrt::name_of<winrt::TabViewItemTemplateSettings>(),
                winrt::name_of<winrt::TabViewItem>(),
                false /* isAttached */,
                ValueHelper<winrt::TabViewItemTemplateSettings>::BoxedDefaultValue(),
                nullptr);
    }
}

void TabViewItemProperties::ClearProperties()
{
    s_HeaderProperty = nullptr;
    s_HeaderTemplateProperty = nullptr;
    s_IconSourceProperty = nullptr;
    s_IsClosableProperty = nullptr;
    s_TabViewTemplateSettingsProperty = nullptr;
}

void TabViewItemProperties::OnHeaderPropertyChanged(
    winrt::DependencyObject const& sender,
    winrt::DependencyPropertyChangedEventArgs const& args)
{
    auto owner = sender.as<winrt::TabViewItem>();
    winrt::get_self<TabViewItem>(owner)->OnHeaderPropertyChanged(args);
}

void TabViewItemProperties::OnIconSourcePropertyChanged(
    winrt::DependencyObject const& sender,
    winrt::DependencyPropertyChangedEventArgs const& args)
{
    auto owner = sender.as<winrt::TabViewItem>();
    winrt::get_self<TabViewItem>(owner)->OnIconSourcePropertyChanged(args);
}

void TabViewItemProperties::OnIsClosablePropertyChanged(
    winrt::DependencyObject const& sender,
    winrt::DependencyPropertyChangedEventArgs const& args)
{
    auto owner = sender.as<winrt::TabViewItem>();
    winrt::get_self<TabViewItem>(owner)->OnIsClosablePropertyChanged(args);
}

void TabViewItemProperties::Header(winrt::IInspectable const& value)
{
    static_cast<TabViewItem*>(this)->SetValue(s_HeaderProperty, ValueHelper<winrt::IInspectable>::BoxValueIfNecessary(value));
}

winrt::IInspectable TabViewItemProperties::Header()
{
    return ValueHelper<winrt::IInspectable>::CastOrUnbox(static_cast<TabViewItem*>(this)->GetValue(s_HeaderProperty));
}

void TabViewItemProperties::HeaderTemplate(winrt::DataTemplate const& value)
{
    static_cast<TabViewItem*>(this)->SetValue(s_HeaderTemplateProperty, ValueHelper<winrt::DataTemplate>::BoxValueIfNecessary(value));
}

winrt::DataTemplate TabViewItemProperties::HeaderTemplate()
{
    return ValueHelper<winrt::DataTemplate>::CastOrUnbox(static_cast<TabViewItem*>(this)->GetValue(s_HeaderTemplateProperty));
}

void TabViewItemProperties::IconSource(winrt::IconSource const& value)
{
    static_cast<TabViewItem*>(this)->SetValue(s_IconSourceProperty, ValueHelper<winrt::IconSource>::BoxValueIfNecessary(value));
}

winrt::IconSource TabViewItemProperties::IconSource()
{
    return ValueHelper<winrt::IconSource>::CastOrUnbox(static_cast<TabViewItem*>(this)->GetValue(s_IconSourceProperty));
}

void TabViewItemProperties::IsClosable(bool value)
{
    static_cast<TabViewItem*>(this)->SetValue(s_IsClosableProperty, ValueHelper<bool>::BoxValueIfNecessary(value));
}

bool TabViewItemProperties::IsClosable()
{
    return ValueHelper<bool>::CastOrUnbox(static_cast<TabViewItem*>(this)->GetValue(s_IsClosableProperty));
}

void TabViewItemProperties::TabViewTemplateSettings(winrt::TabViewItemTemplateSettings const& value)
{
    static_cast<TabViewItem*>(this)->SetValue(s_TabViewTemplateSettingsProperty, ValueHelper<winrt::TabViewItemTemplateSettings>::BoxValueIfNecessary(value));
}

winrt::TabViewItemTemplateSettings TabViewItemProperties::TabViewTemplateSettings()
{
    return ValueHelper<winrt::TabViewItemTemplateSettings>::CastOrUnbox(static_cast<TabViewItem*>(this)->GetValue(s_TabViewTemplateSettingsProperty));
}

winrt::event_token TabViewItemProperties::CloseRequested(winrt::TypedEventHandler<winrt::TabViewItem, winrt::TabViewTabCloseRequestedEventArgs> const& value)
{
    return m_closeRequestedEventSource.add(value);
}

void TabViewItemProperties::CloseRequested(winrt::event_token const& token)
{
    m_closeRequestedEventSource.remove(token);
}
