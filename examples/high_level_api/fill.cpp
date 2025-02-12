/*
 * Copyright 2021 Intel Corporation.
 *
 * This software and the related documents are Intel copyrighted materials,
 * and your use of them is governed by the express license under which they
 * were provided to you ("License"). Unless the License provides otherwise,
 * you may not use, modify, copy, publish, distribute, disclose or transmit
 * this software or the related documents without Intel's prior written
 * permission.
 *
 * This software and the related documents are provided as is, with no
 * express or implied warranties, other than those that are expressly
 * stated in the License.
 *
 */

#include <dml/dml.hpp>
#include <vector>
#include <algorithm>
#include <iostream>

constexpr auto size = 1024u;  // 1 KB

using execution_path = dml::software;

int main()
{
    std::cout << "Starting dml::fill example...\n";
    std::cout << "Fill 1KB of data with a 0x00ABCDEFABCDEF00 pattern\n";

    // Prepare data
    auto pattern = 0x00ABCDEFABCDEF00;
    auto dst = std::vector<std::uint8_t>(size, 0u);

    // Run operation
    auto result = dml::execute<execution_path>(dml::fill, pattern, dml::make_view(dst));

    // Check result
    if (result.status == dml::status_code::ok)
    {
        std::cout << "Finished successfully!\n";
    }
    else
    {
        std::cout << "Failure occurred!\n";
        return -1;
    }


    auto ref = std::vector<std::uint8_t>(size);
    auto ref_data = reinterpret_cast<std::uint64_t*>(ref.data());
    std::fill_n(ref_data, size / sizeof(std::uint64_t), pattern);
    if (ref != dst)
    {
        std::cout << "But operation was done wrongly.\n";
        return -1;
    }

    return 0;
}
