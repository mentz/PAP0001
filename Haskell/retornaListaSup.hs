retornaListaSup :: Int -> [Int] -> [Int]
retornaListaSup _ [] = [] 
retornaListaSup s (h:t) | (h > s) = [h] ++ retornaListaSup s t
                        | otherwise = retornaListaSup s t
