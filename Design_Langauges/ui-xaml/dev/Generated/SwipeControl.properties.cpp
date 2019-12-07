// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

// DO NOT EDIT! This file was generated by CustomTasks.DependencyPropertyCodeGen
#include "pch.h"
#include "common.h"
#include "SwipeControl.h"

CppWinRTActivatableClassWithDPFactory(SwipeControl)

GlobalDependencyProperty SwipeControlProperties::s_BottomItemsProperty{ nullptr };
GlobalDependencyProperty SwipeControlProperties::s_LeftItemsProperty{ nullptr };
GlobalDependencyProperty SwipeControlProperties::s_RightItemsProperty{ nullptr };
GlobalDependencyProperty SwipeControlProperties::s_TopItemsProperty{ nullptr };

SwipeControlProperties::SwipeControlProperties()
{
    EnsureProperties();
}

void SwipeControlProperties::EnsureProperties()
{
    if (!s_BottomItemsProperty)
    {
        s_BottomItemsProperty =
            InitializeDependencyProperty(
                L"BottomItems",
                winrt::name_of<winrt::SwipeItems>(),
                winrt::name_of<winrt::SwipeControl>(),
                false /* isAttached */,
                ValueHelper<winrt::SwipeItems>::BoxedDefaultValue(),
                winrt::PropertyChangedCallback(&OnBottomItemsPropertyChanged));
    }
    if (!s_LeftItemsProperty)
    {
        s_LeftItemsProperty =
            InitializeDependencyProperty(
                L"LeftItems",
                winrt::name_of<winrt::SwipeItems>(),
                winrt::name_of<winrt::SwipeControl>(),
                false /* isAttached */,
                ValueHelper<winrt::SwipeItems>::BoxedDefaultValue(),
                winrt::PropertyChangedCallback(&OnLeftItemsPropertyChanged));
    }
    if (!s_RightItemsProperty)
    {
        s_RightItemsProperty =
            InitializeDependencyProperty(
                L"RightItems",
                winrt::name_of<winrt::SwipeItems>(),
                winrt::name_of<winrt::SwipeControl>(),
                false /* isAttached */,
                ValueHelper<winrt::SwipeItems>::BoxedDefaultValue(),
                winrt::PropertyChangedCallback(&OnRightItemsPropertyChanged));
    }
    if (!s_TopItemsProperty)
    {
        s_TopItemsProperty =
            InitializeDependencyProperty(
                L"TopItems",
                winrt::name_of<winrt::SwipeItems>(),
                winrt::name_of<winrt::SwipeControl>(),
                false /* isAttached */,
                ValueHelper<winrt::SwipeItems>::BoxedDefaultValue(),
                winrt::PropertyChangedCallback(&OnTopItemsPropertyChanged));
    }
}

void SwipeControlProperties::ClearProperties()
{
    s_BottomItemsProperty = nullptr;
    s_LeftItemsProperty = nullptr;
    s_RightItemsProperty = nullptr;
    s_TopItemsProperty = nullptr;
}

void SwipeControlProperties::OnBottomItemsPropertyChanged(
    winrt::DependencyObject const& sender,
    winrt::DependencyPropertyChangedEventArgs const& args)
{
    auto owner = sender.as<winrt::SwipeControl>();
    winrt::get_self<SwipeControl>(owner)->OnPropertyChanged(args);
}

void SwipeControlProperties::OnLeftItemsPropertyChanged(
    winrt::DependencyObject const& sender,
    winrt::DependencyPropertyChangedEventArgs const& args)
{
    auto owner = sender.as<winrt::SwipeControl>();
    winrt::get_self<SwipeControl>(owner)->OnPropertyChanged(args);
}

void SwipeControlProperties::OnRightItemsPropertyChanged(
    winrt::DependencyObject const& sender,
    winrt::DependencyPropertyChangedEventArgs const& args)
{
    auto owner = sender.as<winrt::SwipeControl>();
    winrt::get_self<SwipeControl>(owner)->OnPropertyChanged(args);
}

void SwipeControlProperties::OnTopItemsPropertyChanged(
    winrt::DependencyObject const& sender,
    winrt::DependencyPropertyChangedEventArgs const& args)
{
    auto owner = sender.as<winrt::SwipeControl>();
    winrt::get_self<SwipeControl>(owner)->OnPropertyChanged(args);
}

void SwipeControlProperties::BottomItems(winrt::SwipeItems const& value)
{
    static_cast<SwipeControl*>(this)->SetValue(s_BottomItemsProperty, ValueHelper<winrt::SwipeItems>::BoxValueIfNecessary(value));
}

winrt::SwipeItems SwipeControlProperties::BottomItems()
{
    return ValueHelper<winrt::SwipeItems>::CastOrUnbox(static_cast<SwipeControl*>(this)->GetValue(s_BottomItemsProperty));
}

void SwipeControlProperties::LeftItems(winrt::SwipeItems const& value)
{
    static_cast<SwipeControl*>(this)->SetValue(s_LeftItemsProperty, ValueHelper<winrt::SwipeItems>::BoxValueIfNecessary(value));
}

winrt::SwipeItems SwipeControlProperties::LeftItems()
{
    return ValueHelper<winrt::SwipeItems>::CastOrUnbox(static_cast<SwipeControl*>(this)->GetValue(s_LeftItemsProperty));
}

void SwipeControlProperties::RightItems(winrt::SwipeItems const& value)
{
    static_cast<SwipeControl*>(this)->SetValue(s_RightItemsProperty, ValueHelper<winrt::SwipeItems>::BoxValueIfNecessary(value));
}

winrt::SwipeItems SwipeControlProperties::RightItems()
{
    return ValueHelper<winrt::SwipeItems>::CastOrUnbox(static_cast<SwipeControl*>(this)->GetValue(s_RightItemsProperty));
}

void SwipeControlProperties::TopItems(winrt::SwipeItems const& value)
{
    static_cast<SwipeControl*>(this)->SetValue(s_TopItemsProperty, ValueHelper<winrt::SwipeItems>::BoxValueIfNecessary(value));
}

winrt::SwipeItems SwipeControlProperties::TopItems()
{
    return ValueHelper<winrt::SwipeItems>::CastOrUnbox(static_cast<SwipeControl*>(this)->GetValue(s_TopItemsProperty));
}