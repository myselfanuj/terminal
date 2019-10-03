/*++
Copyright (c) Microsoft Corporation
Licensed under the MIT license.

Module Name:
- CascadiaSettings.hpp

Abstract:
- This class encapsulates all of the settings that are global to the app, and
    not a part of any particular profile.

Author(s):
- Mike Griese - March 2019

--*/
#pragma once
#include "AppKeyBindings.h"
#include "ColorScheme.h"

// fwdecl unittest classes
namespace TerminalAppLocalTests
{
    class SettingsTests;
    class ColorSchemeTests;
};

namespace TerminalApp
{
    class GlobalAppSettings;
};

class TerminalApp::GlobalAppSettings final
{
public:
    GlobalAppSettings();
    ~GlobalAppSettings();

    std::unordered_map<std::wstring, ColorScheme>& GetColorSchemes() noexcept;
    const std::unordered_map<std::wstring, ColorScheme>& GetColorSchemes() const noexcept;
    void AddScheme(ColorScheme scheme);

    void SetDefaultProfile(const GUID defaultProfile) noexcept;
    GUID GetDefaultProfile() const noexcept;

    winrt::TerminalApp::AppKeyBindings GetKeybindings() const noexcept;

    bool GetAlwaysShowTabs() const noexcept;
    void SetAlwaysShowTabs(const bool showTabs) noexcept;

    bool GetShowTitleInTitlebar() const noexcept;
    void SetShowTitleInTitlebar(const bool showTitleInTitlebar) noexcept;

    void SetRequestedTheme(const winrt::Windows::UI::Xaml::ElementTheme requestedTheme) noexcept;

    bool GetShowTabsInTitlebar() const noexcept;
    void SetShowTabsInTitlebar(const bool showTabsInTitlebar) noexcept;

    std::wstring GetWordDelimiters() const noexcept;
    void SetWordDelimiters(const std::wstring wordDelimiters) noexcept;

    bool GetCopyOnSelect() const noexcept;
    void SetCopyOnSelect(const bool copyOnSelect) noexcept;

    winrt::Windows::UI::Xaml::ElementTheme GetRequestedTheme() const noexcept;

    Json::Value ToJson() const;
    static GlobalAppSettings FromJson(const Json::Value& json);
    void LayerJson(const Json::Value& json);

    void ApplyToSettings(winrt::Microsoft::Terminal::Settings::TerminalSettings& settings) const noexcept;

private:
    GUID _defaultProfile;
    winrt::com_ptr<winrt::TerminalApp::implementation::AppKeyBindings> _keybindings;

    std::unordered_map<std::wstring, ColorScheme> _colorSchemes;

    int32_t _initialRows;
    int32_t _initialCols;

    bool _showStatusline;
    bool _alwaysShowTabs;
    bool _showTitleInTitlebar;

    bool _showTabsInTitlebar;
    std::wstring _wordDelimiters;
    bool _copyOnSelect;
    winrt::Windows::UI::Xaml::ElementTheme _requestedTheme;

    static winrt::Windows::UI::Xaml::ElementTheme _ParseTheme(const std::wstring& themeString) noexcept;
    static std::wstring_view _SerializeTheme(const winrt::Windows::UI::Xaml::ElementTheme theme) noexcept;

    friend class TerminalAppLocalTests::SettingsTests;
    friend class TerminalAppLocalTests::ColorSchemeTests;
};
