sort :: [Int] -> [Int]
sort [] = []
sort (h:t) = sort [l | l <- t, l < h] ++ [h] ++ sort [g | g <- t, g >= h]

