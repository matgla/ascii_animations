/*
 Copyright (c) 2025 Mateusz Stadnik

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>

#include "rain.h"

int main(int argc, char *argv[]) {
  // Check if the user provided a command-line argument
  if (argc < 2) {
    printf("Usage: %s <name>\n", argv[0]);
    printf("Provide a name of animation:\n");
    printf("  - rain\n");

    return 1;
  }

  if (strcmp(argv[1], "rain") == 0) {
    rain();
  } else {
    printf("Unknown animation: %s\n", argv[1]);
  }

  return 0;
}