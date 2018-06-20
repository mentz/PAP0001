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

-- 7: Uso Integer para permitir inteiros grandes
testaFatores :: (Integer, Integer) -> Bool
testaFatores (a,p) | a * a > p = True
                   | (mod p a) == 0 = False
                   | otherwise = testaFatores (a + 1, p)

ePrimo :: Integer -> Bool
ePrimo a | a <= 3 = True
         | otherwise = testaFatores (2,a)

-- 8: Uso Integer pois podem ser bem grandes
fatorial :: Integer -> Integer
fatorial 1 = 1
fatorial f = f * (fatorial (f - 1))

-- 9: Não otimizado, pesa bastante com a > 25
fibonacci :: Integer -> Integer
fibonacci 0 = 0
fibonacci 1 = 1
fibonacci a = fibonacci (a-2) + fibonacci (a-1)

-- 10: 1-indexado
elemento :: [a] -> Int -> a
elemento (h:t) 1 = h
elemento (h:t) p = elemento t (p-1)

-- 11
pertence :: (Eq a) => a -> [a] -> Bool
pertence a [] = False
pertence a (h:t) | a == h = True
                 | otherwise = pertence a t

-- 12
nroElementos :: [a] -> Integer
nroElementos [] = 0
nroElementos (h:t) = 1 + nroElementos t

-- 13
maior :: [Integer] -> Integer
maior [t] = t
maior (h:t) = max h (maior t)

-- 14
contaOcorrencias :: (Eq a) => a -> [a] -> Integer
contaOcorrencias a [] = 0
contaOcorrencias a (h:t) | a == h = 1 + contaOcorrencias a t
                         | otherwise = 0 + contaOcorrencias a t

-- 15
unicaOcorrencia :: (Eq a) => a -> [a] -> Bool
unicaOcorrencia a (h:t) | contaOcorrencias a (h:t) == 1 = True
                        | otherwise = False

-- 16
maioresQue :: Integer -> [Integer] -> [Integer]
maioresQue a [] = []
maioresQue a (h:t) | h > a = [h] ++ maioresQue a t
                   | otherwise = maioresQue a t

-- 17
concatena :: [a] -> [a] -> [a]
concatena (h1:t1) (h2:t2) = [h1] ++ t1 ++ [h2] ++ t2

-- 18
remover :: (Eq a) => a -> [a] -> [a]
remover a [] = []
remover a (h:t) | a == h = t
                | otherwise = [h] ++ remover a t

-- 19
removerUltimo :: [a] -> [a]
removerUltimo [] = []
removerUltimo [a] = []
removerUltimo (h:t) = [h] ++ removerUltimo t

-- 20: A terminar
--removerRepetidos :: (Eq a) => [a] -> [a]
--removerRepetidos [] = []
--removerRepetidos (h:t) | 
