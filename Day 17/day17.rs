use std::collections::HashSet;
use std::fs;

fn can_push(rock: &Vec<usize>, occupied: &HashSet<usize>, dir: char) -> bool {
    for pos in rock{
        let new_pos = match dir {
            '>' => *pos + 1,
            '<' => *pos - 1,
            _ => panic!("What direction!"),
        };
        if new_pos / 7 != *pos / 7 || occupied.contains(&new_pos) {
            return false;
        }
    }
    true
}

fn can_proceed_downward(rock: &Vec<usize>, occupied: &HashSet<usize>) -> bool {
    for pos in rock {
        if *pos < 7usize || occupied.contains(&(*pos - 7)) {
            return false;
        }
    }
    true
}



fn main() {
    // Idea:
    // The available spot will be indexed as
    // | 35 36 37 38 39 40 41 |
    // | 28 29 30 31 32 33 34 |
    // | 21 22 23 24 25 26 27 |
    // | 14 15 16 17 18 19 20 |
    // |  7  8  9 10 11 12 13 |
    // |  0  1  2  3  4  5  6 |
    // ------------------------

    let fp = "./day17.input.txt";
    let jet_pattern = fs::read_to_string(fp).expect("No such file");
    let mut occupied = HashSet::new();
    let mut highest_val: usize = 0;
    let mut highest_row: usize = 0;
    let rocks: Vec<Vec<usize>> = vec![
        vec![2, 3, 4, 5],       // horizontal bar
        vec![3, 9, 10, 11, 17], // cross
        vec![2, 3, 4, 11, 18],  // reversed L
        vec![2, 9, 16, 23],     // vertical bar
        vec![2, 3, 9, 10],      // square
    ];
    let mut curr_jet_index = 0;
    let mut curr_rock_index = 0;

    for _ in 1..2023 {
        let mut curr_rock: Vec<usize> = rocks[curr_rock_index].iter().map(|v| *v + (highest_row + 3) * 7).collect();
        // println!("Initial: {:?}", curr_rock);
        loop {
            // push
            if can_push(&curr_rock, &occupied, jet_pattern.as_bytes()[curr_jet_index] as char) {
                for pos in curr_rock.iter_mut() {
                    *pos = match jet_pattern.as_bytes()[curr_jet_index] as char {
                        '>' => *pos + 1,
                        '<' => *pos - 1,
                        _ => panic!("What direction!"),
                    }
                }
            }
            // println!("Push: {:?}", curr_rock);
            
            // downward
            if can_proceed_downward(&curr_rock, &occupied) {
                for pos in curr_rock.iter_mut() {
                    *pos -= 7;
                }
                // println!("Down: {:?}", curr_rock);
            } else {
                curr_jet_index = (curr_jet_index + 1) % jet_pattern.len();
                break;
            }

            curr_jet_index = (curr_jet_index + 1) % jet_pattern.len();
        }
        for pos in curr_rock {
            occupied.insert(pos);
            highest_val = if pos > highest_val { pos } else { highest_val };
        }
        highest_row = highest_val / 7 + 1;
        curr_rock_index = (curr_rock_index + 1) % rocks.len();
    }
    println!("{}", highest_row);
    // println!("{:?}", occupied);
}
