/*
 * Copyright (c) 2019 - 2025 Geode-solutions
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#pragma once

#include <geode/basic/attribute_utils.hpp>
#include <geode/basic/range.hpp>

#include <geode/image/common.hpp>

namespace geode
{
    class opengeode_image_api GreyscaleColor
    {
    public:
        GreyscaleColor();

        explicit GreyscaleColor( local_index_t value );

        [[nodiscard]] local_index_t value() const;

        void set_value( local_index_t greyscale );

        [[nodiscard]] bool operator==( const GreyscaleColor &other ) const;

        [[nodiscard]] bool operator!=( const GreyscaleColor &other ) const;

        [[nodiscard]] GreyscaleColor operator+(
            const GreyscaleColor &other ) const;

        void operator+=( const GreyscaleColor &other );

        [[nodiscard]] std::string string() const;

    private:
        friend class bitsery::Access;
        template < typename Archive >
        void serialize( Archive &archive );

    private:
        local_index_t value_;
    };

    template <>
    struct AttributeLinearInterpolationImpl< GreyscaleColor >
    {
        template < template < typename > class Attribute >
        static GreyscaleColor compute(
            const AttributeLinearInterpolation &interpolator,
            const Attribute< GreyscaleColor > &attribute )
        {
            local_index_t result{ 0 };
            bool is_same{ true };
            const auto &first_value =
                attribute.value( interpolator.indices_[0] ).value();
            for( const auto i : Indices{ interpolator.indices_ } )
            {
                const auto &i_value =
                    attribute.value( interpolator.indices_[i] ).value();
                if( is_same )
                {
                    is_same = i_value == first_value;
                }
                result = result + i_value * interpolator.lambdas_[i];
            }
            if( is_same )
            {
                return GreyscaleColor{ first_value };
            }
            return GreyscaleColor{ result };
        }
    };

    template <>
    struct GenericAttributeConversion< GreyscaleColor >
    {
        static float converted_value( const GreyscaleColor &color )
        {
            return color.value();
        }

        static float converted_item_value(
            const GreyscaleColor &color, local_index_t item )
        {
            geode_unused( item );
            OPENGEODE_ASSERT( item < nb_items(),
                "[GenericAttributeConversion] Accessing "
                "incorrect item value" );
            return static_cast< float >( color.value() );
        }

        static bool is_genericable()
        {
            return true;
        }
        static local_index_t nb_items()

        {
            return 1;
        }
    };
} // namespace geode

namespace std
{
    template <>
    struct opengeode_image_api hash< geode::GreyscaleColor >
    {
        size_t operator()( const geode::GreyscaleColor &color ) const;
    };
} // namespace std
