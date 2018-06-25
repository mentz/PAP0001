invert :: [a] -> [a]
invert [] = []
invert (h:t) = (invert t) ++ [h]
