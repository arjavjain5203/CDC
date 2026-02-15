def create_house(length, height, direction):
    """Create a house with given dimensions and orientation"""
    
    if direction == 'H':  # Normal house (no tilt)
        lines = []
        # Roof - triangular
        roof_height = (length + 1) // 2
        for i in range(roof_height):
            spaces = ' ' * (roof_height - i - 1)
            if i == 0 and length % 2 == 0:
                roof_line = '/' + ' ' * (2 * i) + '\\'
            else:
                roof_line = '/' + ' ' * (2 * i) + '\\'
            lines.append(spaces + roof_line)
        
        # Walls
        for _ in range(height):
            lines.append('@' + ' ' * length + '&')
        
        # Base
        lines.append('#' * (length + 2))
        return lines
    
    elif direction == 'U':  # Tilted upward
        lines = []
        roof_height = (length + 1) // 2
        
        # Roof pointing up
        for i in range(roof_height):
            if i == 0:
                line = ' ' * (length // 2) + '∧'
            else:
                spaces = ' ' * (roof_height - i - 1)
                middle = ' ' * (2 * i - 1)
                line = spaces + '/' + middle + '\\'
            lines.append(line)
        
        # Slanted walls going up
        for i in range(height):
            spaces = ' ' * (height - i - 1)
            middle = ' ' * (length + 2 * i)
            line = spaces + '/' + middle + '\\'
            lines.append(line)
        
        # Base
        base_spaces = ' ' * (height - 1)
        lines.append(base_spaces + '#' * (length + 2))
        return lines
    
    elif direction == 'D':  # Tilted downward
        lines = []
        
        # Top slanted part (roof going down)
        slant_height = min(height, (length + 1) // 2)
        for i in range(slant_height):
            spaces = ' ' * i
            middle = ' ' * (length + 2 * (slant_height - i - 1))
            line = spaces + '\\' + middle + '/'
            lines.append(line)
        
        # Remaining vertical walls
        remaining_height = height - slant_height
        for i in range(remaining_height):
            spaces = ' ' * slant_height
            line = spaces + '@' + ' ' * length + '&'
            lines.append(line)
        
        # Base
        base_spaces = ' ' * slant_height
        lines.append(base_spaces + '#' * (length + 2))
        return lines
    
    elif direction == 'L':  # Tilted left
        # For left tilt, we need to build a grid
        total_height = height + (length + 1) // 2 + 1
        total_width = length + (length + 1) // 2 + 1
        
        # Create empty grid
        grid = [[' '] * total_width for _ in range(total_height)]
        
        # Draw slanted roof on left side
        roof_height = (length + 1) // 2
        for i in range(roof_height):
            row = total_height - i - 1
            left_col = i
            right_col = left_col + length + 1
            if row < total_height and left_col < total_width:
                grid[row][left_col] = '/'
            if row < total_height and right_col < total_width:
                grid[row][right_col] = '\\'
        
        # Draw vertical walls
        for i in range(height):
            row = total_height - roof_height - i - 1
            if row >= 0:
                grid[row][0] = '@'
                if length + 1 < total_width:
                    grid[row][length + 1] = '&'
        
        # Draw base at bottom
        base_row = total_height - roof_height - height - 1
        if base_row >= 0:
            for i in range(length + 2):
                if i < total_width:
                    grid[base_row][i] = '#'
        
        # Convert grid to lines, remove trailing spaces
        lines = []
        for row in grid:
            line = ''.join(row).rstrip()
            if line:  # Only add non-empty lines
                lines.append(line)
        return lines
    
    elif direction == 'R':  # Tilted right
        # For right tilt, similar to left but mirrored
        total_height = height + (length + 1) // 2 + 1
        total_width = length + (length + 1) // 2 + 1
        
        # Create empty grid
        grid = [[' '] * total_width for _ in range(total_height)]
        
        # Draw slanted roof on right side
        roof_height = (length + 1) // 2
        offset = height
        for i in range(roof_height):
            row = i
            left_col = offset
            right_col = left_col + length + 1
            if row < total_height and left_col < total_width:
                grid[row][left_col] = '\\'
            if row < total_height and right_col < total_width:
                grid[row][right_col] = '/'
        
        # Draw vertical walls on right side
        for i in range(height):
            row = roof_height + i
            if row < total_height and offset < total_width:
                grid[row][offset] = '@'
            if row < total_height and (offset + length + 1) < total_width:
                grid[row][offset + length + 1] = '&'
        
        # Draw base
        base_row = roof_height + height
        if base_row < total_height:
            for i in range(length + 2):
                if offset + i < total_width:
                    grid[base_row][offset + i] = '#'
        
        # Convert grid to lines
        lines = []
        for row in grid:
            line = ''.join(row).rstrip()
            if line:
                lines.append(line)
        return lines

def align_houses(houses):
    """Align all houses to sit on the same baseline"""
    if not houses:
        return []
    
    # Find maximum height
    max_height = max(len(house) for house in houses)
    
    # Align by padding at the top
    aligned_houses = []
    for house in houses:
        current_height = len(house)
        padding = max_height - current_height
        aligned_house = [''] * padding + house
        aligned_houses.append(aligned_house)
    
    return aligned_houses

def combine_houses(aligned_houses):
    """Combine aligned houses side by side"""
    if not aligned_houses:
        return []
    
    result_lines = []
    num_lines = len(aligned_houses[0])
    
    for line_num in range(num_lines):
        combined_line = ''
        for house in aligned_houses:
            if line_num < len(house) and house[line_num]:
                # Add this house's line
                combined_line += house[line_num]
            else:
                # Add spaces for alignment (use width of first non-empty line)
                if house and house[0]:
                    combined_line += ' ' * len(house[0])
                else:
                    combined_line += ' '
        
        result_lines.append(combined_line.rstrip())
    
    return result_lines

def main():
    import sys
    
    # Read input
    input_data = sys.stdin.read().strip()
    if not input_data:
        return
    
    specifications = input_data.split()
    houses = []
    
    for spec in specifications:
        # Parse specification: format is like "6x3U", "4x2U", etc.
        x_pos = spec.find('x')
        if x_pos == -1:
            continue
            
        # Find the direction character
        dir_char = None
        for char in spec[x_pos:]:
            if char in 'UDLRH':
                dir_char = char
                break
        
        if not dir_char:
            continue
            
        dir_pos = spec.find(dir_char)
        length = int(spec[:x_pos])
        height = int(spec[x_pos+1:dir_pos])
        direction = dir_char
        
        # Create the house
        house = create_house(length, height, direction)
        houses.append(house)
    
    # Align and combine houses
    aligned_houses = align_houses(houses)
    result = combine_houses(aligned_houses)
    
    # Print the result
    for line in result:
        print(line)

# Test function to verify with the given examples
def test_examples():
    """Test the function with the provided examples"""
    
    print("Testing Example 1: 6x3U 4x2U 8x4L 2x2H")
    print("=" * 50)
    
    # Test case 1
    test_input = "6x3U 4x2U 8x4L 2x2H"
    specifications = test_input.split()
    houses = []
    
    for spec in specifications:
        x_pos = spec.find('x')
        dir_char = None
        for char in spec[x_pos:]:
            if char in 'UDLRH':
                dir_char = char
                break
        
        if not dir_char:
            continue
            
        dir_pos = spec.find(dir_char)
        length = int(spec[:x_pos])
        height = int(spec[x_pos+1:dir_pos])
        direction = dir_char
        
        house = create_house(length, height, direction)
        houses.append(house)
    
    aligned_houses = align_houses(houses)
    result = combine_houses(aligned_houses)
    
    for line in result:
        print(line)
    
    print("\n" + "=" * 50)
    print("Testing Example 2: 4x6R 12x8H 2x6D")
    print("=" * 50)
    
    # Test case 2
    test_input2 = "4x6R 12x8H 2x6D"
    specifications2 = test_input2.split()
    houses2 = []
    
    for spec in specifications2:
        x_pos = spec.find('x')
        dir_char = None
        for char in spec[x_pos:]:
            if char in 'UDLRH':
                dir_char = char
                break
        
        if not dir_char:
            continue
            
        dir_pos = spec.find(dir_char)
        length = int(spec[:x_pos])
        height = int(spec[x_pos+1:dir_pos])
        direction = dir_char
        
        house = create_house(length, height, direction)
        houses2.append(house)
    
    aligned_houses2 = align_houses(houses2)
    result2 = combine_houses(aligned_houses2)
    
    for line in result2:
        print(line)

if __name__ == "__main__":
    # Uncomment the next line to test with examples
    # test_examples()
    
    # Use this for actual input
    main()