#pragma once

#include "ProjectCore/FLog.h"

namespace ProjectCore::Tester
{
    class CopyMoveCheck
    {
    public:
        static inline FLog::BasicLogger Logger;

    public:
        CopyMoveCheck(const std::string& name) 
            : m_Name(name)
        {
            Logger.Info("CopyMoveCheck {} : {:C:red} ( {:C:red} )", m_Name, "Default (copy string) Constructor", "TestCopy(const std::string& name)");
        }

        CopyMoveCheck(std::string&& name)
            : m_Name(std::move(name))
        {
            Logger.Info("CopyMoveCheck {} : {:C:red} ( {:C:red} )", m_Name, "Default (move string) Constructor", "TestCopy(std::string&& name)");
        }


        CopyMoveCheck(CopyMoveCheck& other)
            : m_Name("Copy of " + other.m_Name)
        {
            Logger.Info("CopyMoveCheck {} : {:C:red} ( {:C:red} )", m_Name, "Copy Constructor", "TestCopy(TestCopy&)");
        }

        CopyMoveCheck(const CopyMoveCheck& other)
            : m_Name("Copy of " + other.m_Name) 
        {
            Logger.Info("CopyMoveCheck {} : {:C:red} ( {:C:red} )", m_Name, "Const Copy Constructor", "TestCopy(const TestCopy&)");
        }

        CopyMoveCheck(CopyMoveCheck&& other) noexcept
            : m_Name("Move of " + other.m_Name) 
        {
            Logger.Info("CopyMoveCheck {} : {:C:red} ( {:C:red} )", m_Name, "Move Constructor", "TestCopy(TestCopy&&)");
        }

        CopyMoveCheck(const CopyMoveCheck&& other) noexcept
            : m_Name("Move of " + other.m_Name) 
        {
            Logger.Info("CopyMoveCheck {} : {:C:red} ( {:C:red} )", m_Name, "Const Move Constructor", "TestCopy(const TestCopy&&)");
        }


        CopyMoveCheck& operator=(CopyMoveCheck& other) {

            m_Name = "Copy Of " + other.m_Name;

            Logger.Info("CopyMoveCheck {} : {:C:red} ( {:C:red} )", m_Name, "Copy Assignment", "TestCopy& operator=(TestCopy&)");
            return *this;
        }

        CopyMoveCheck& operator=(const CopyMoveCheck& other) {

            m_Name = "Copy Of " + other.m_Name;

            Logger.Info("CopyMoveCheck {} : {:C:red} ( {:C:red} )", m_Name, "Const Copy Assignment", "TestCopy& operator=(const TestCopy&)");
            return *this;
        }

        CopyMoveCheck& operator=(CopyMoveCheck&& other) noexcept {

            m_Name = "Move Of " + other.m_Name;

            Logger.Info("CopyMoveCheck {} : {:C:red} ( {:C:red} )", m_Name, "Move Assignment", "TestCopy& operator=(TestCopy&&)");
            return *this;
        }

        CopyMoveCheck& operator=(const CopyMoveCheck&& other) noexcept {

            m_Name = "Move Of " + other.m_Name;

            Logger.Info("CopyMoveCheck {} : {:C:red} ( {:C:red} )", m_Name, "Const Move Assignment", "TestCopy& operator=(const TestCopy&&)");
            return *this;
        }

    private:
        std::string m_Name;
    };
}

