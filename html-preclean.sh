#!/bin/bash

set -euo pipefail

mv counting-in-cpp/counting-in-c++.html counting-in-cpp/index.html

sed "s/\(Naming quality: .*\).*\(<\/span>. Would have put zero stars\)/\1★☆☆☆☆\2/g" -i counting-in-cpp/counting-in-c++su12.html

tidy --hide-comments yes --quote-nbsp no -modify -quiet counting-in-cpp/*.html \
    || true

