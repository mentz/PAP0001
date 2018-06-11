retornaSup :: Int -> [Int] -> Int
retornaSup _ [] = 0
retornaSup x (h:t) | (h > x) = 1 + retornaSup x (t)
                   | otherwise = retornaSup x (t)
