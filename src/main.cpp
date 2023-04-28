#include <iostream>
#include <vector>
#include <span>
#include <map>

import cpp_script;

auto main() -> int {
    auto stream = TokenStream(R"(
        auto a = 10 + 11 * (12 - 13) * -1;
        auto b = a + 1;
        auto c = a + b;
        print(a, b, c);
    )");
    stream.readToken();
    evaluate(stream);
    return 0;
}
