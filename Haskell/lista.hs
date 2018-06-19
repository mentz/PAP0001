-- Autor: Lucas Litter Mentz

-- 1
soma :: (Int, Int) -> Int
soma (a,b) = a + b

-- 2
menorDeDois :: (Int, Int) -> Int
menorDeDois (a,b) | a < b = a
                  | otherwise = b

-- 3
menorDeTres :: (Int, Int, Int) -> Int
menorDeTres (a,b,c) = menorDeDois (menorDeDois (a,b), c)

-- 4
areaCircunf :: Float -> Float
areaCircunf r = pi * r * r

-- 5
andTres :: (Bool, Bool, Bool) -> Bool
andTres (a,b,c) = and [and [a, b], c]

-- 6
(#) :: [Char] -> [Char] -> [Char]
(#) a b | a == b = a
        | otherwise = a ++ b

-- 7
-- TODO implementar um modo de determinar primalidade
-- acho que pode ser uma função recursiva que varre de trás
-- para frente os ímpares a partir de sqrt(candidato) até 1
-- verificando o resto de divisão. Se nenhum der 0, é primo.
ePrimo :: Int -> Bool
ePrimo a | a <= 3 = True
         | otherwise = testaFatores ceil(sqrt a) a
