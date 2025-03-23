#pragma once

#include "stream/flog.h"

namespace stream::tester
{
    class CopyMoveCheck
    {
    public:
        static inline flog::BasicLogger logger;

    public:
        CopyMoveCheck(const std::string& name)
            : name_(name)
        {
            logger.info("CopyMoveCheck {} : {:C:red} ( {:C:red} )", name_, "Default (copy string) Constructor", "TestCopy(const std::string& name)");
        }

        CopyMoveCheck(std::string&& name)
            : name_(std::move(name))
        {
            logger.info("CopyMoveCheck {} : {:C:red} ( {:C:red} )", name_, "Default (move string) Constructor", "TestCopy(std::string&& name)");
        }

        CopyMoveCheck(CopyMoveCheck& other)
            : name_("Copy of " + other.name_)
        {
            logger.info("CopyMoveCheck {} : {:C:red} ( {:C:red} )", name_, "Copy Constructor", "TestCopy(TestCopy&)");
        }

        CopyMoveCheck(const CopyMoveCheck& other)
            : name_("Copy of " + other.name_)
        {
            logger.info("CopyMoveCheck {} : {:C:red} ( {:C:red} )", name_, "Const Copy Constructor", "TestCopy(const TestCopy&)");
        }

        CopyMoveCheck(CopyMoveCheck&& other) noexcept
            : name_("Move of " + other.name_)
        {
            logger.info("CopyMoveCheck {} : {:C:red} ( {:C:red} )", name_, "Move Constructor", "TestCopy(TestCopy&&)");
        }

        CopyMoveCheck(const CopyMoveCheck&& other) noexcept
            : name_("Move of " + other.name_)
        {
            logger.info("CopyMoveCheck {} : {:C:red} ( {:C:red} )", name_, "Const Move Constructor", "TestCopy(const TestCopy&&)");
        }

        CopyMoveCheck& operator=(CopyMoveCheck& other)
        {
            name_ = "Copy Of " + other.name_;

            logger.info("CopyMoveCheck {} : {:C:red} ( {:C:red} )", name_, "Copy Assignment", "TestCopy& operator=(TestCopy&)");
            return *this;
        }

        CopyMoveCheck& operator=(const CopyMoveCheck& other)
        {
            name_ = "Copy Of " + other.name_;

            logger.info("CopyMoveCheck {} : {:C:red} ( {:C:red} )", name_, "Const Copy Assignment", "TestCopy& operator=(const TestCopy&)");
            return *this;
        }

        CopyMoveCheck& operator=(CopyMoveCheck&& other) noexcept
        {
            name_ = "Move Of " + other.name_;

            logger.info("CopyMoveCheck {} : {:C:red} ( {:C:red} )", name_, "Move Assignment", "TestCopy& operator=(TestCopy&&)");
            return *this;
        }

        CopyMoveCheck& operator=(const CopyMoveCheck&& other) noexcept
        {
            name_ = "Move Of " + other.name_;

            logger.info("CopyMoveCheck {} : {:C:red} ( {:C:red} )", name_, "Const Move Assignment", "TestCopy& operator=(const TestCopy&&)");
            return *this;
        }

    private:
        std::string name_;
    };
}
