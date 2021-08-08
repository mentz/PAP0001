-- Autor: Lucas Litter Mentz
import Data.Char -- para uso nas 34 e 35

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
elemento [] _ = error "Posição excede tamanho do vetor"
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

-- 20
auxRemoverRepetidos :: (Eq a) => a -> [a] -> [a]
auxRemoverRepetidos a [] = []
auxRemoverRepetidos a (h:t) | a == h = auxRemoverRepetidos a t
                            | otherwise = [h] ++ auxRemoverRepetidos a t

removerRepetidos :: (Eq a) => [a] -> [a]
removerRepetidos [] = []
removerRepetidos (h:t) = [h] ++ removerRepetidos (auxRemoverRepetidos h t) 

-- 21
maiores :: Integer -> [Integer] -> [Integer]
maiores a [] = []
maiores a (h:t) | a < 0 = error "Entre com um natural."
                | h > a = [h] ++ maiores a t
                | otherwise = maiores a t

-- 22
geraSequencia :: Integer -> [Integer]
geraSequencia 0 = []
geraSequencia n | n < 0 = error "Entre com um inteiro positivo."
                | otherwise = geraSequencia (n-1) ++ [n, -n]

-- 23
inverte :: [a] -> [a]
inverte [] = []
inverte (h:t) = inverte t ++ [h]

-- 24
auxDivideEsq :: Integer -> [a] -> [a]
auxDivideEsq 0 (h:t) = []
auxDivideEsq a (h:t) = [h] ++ auxDivideEsq (a-1) t
auxDivideDir :: Integer -> [a] -> [a]
auxDivideDir 0 (h:t) = (h:t)
auxDivideDir a (h:t) = auxDivideDir (a-1) t

divide :: Integer -> [Integer] -> ([Integer], [Integer])
divide a b | a < 0 = error "Entre com um natural."
           | otherwise = (auxDivideEsq a b, auxDivideDir a b)

-- 25
intercala :: [a] -> [a] -> [a]
intercala [] b = b
intercala a [] = a
intercala (h1:t1) (h2:t2) = [h1] ++ [h2] ++ intercala t1 t2

-- 26
uniao :: (Eq a) => [a] -> [a] -> [a]
uniao [] b = b
uniao a [] = a
uniao a (h:t) | pertence h a = uniao a t
              | otherwise = uniao a t ++ [h]

-- 27
intersecao :: (Eq a) => [a] -> [a] -> [a]
intersecao _ [] = []
intersecao [] _ = []
intersecao a (h2:t2) | pertence h2 a = [h2] ++ intersecao a t2
                     | otherwise = intersecao a t2

-- 28
sequencia :: Integer -> Integer -> [Integer]
sequencia 0 _ = []
sequencia n m = [m] ++ sequencia (n-1) (m+1)

-- 29
insereOrdenado :: (Ord a) => [a] -> a -> [a]
insereOrdenado [] a = [a]
insereOrdenado (h:t) a | a < h = [a] ++ (h:t)
                       | otherwise = [h] ++ insereOrdenado t a

-- 30: Ordenado (em ordem crescente)
ordenado :: (Ord a) => [a] -> Bool
ordenado [a] = True
ordenado [a,b] = a <= b
ordenado (h:m:t) | h <= m = ordenado (m:t)
                 | otherwise = False

-- 31: Usa quicksort
ordena :: (Ord a) => [a] -> [a]
ordena [] = []
ordena (h:t) = ordena [a | a <- t, a < h] ++ [h] ++ ordena [a | a <- t, a >= h]

-- 32
rodarEsquerda :: Int -> [a] -> [a]
rodarEsquerda 0 b = b
rodarEsquerda n (h:t) = rodarEsquerda (n-1) (t ++ [h])

-- 33
rodarDireita :: Int -> [a] -> [a]
rodarDireita n b = rodarEsquerda ((length b) - (mod n (length b))) b

-- 34
todasMaiusculas :: String -> String
todasMaiusculas [] = []
todasMaiusculas (h:t)
   | and (((ord h) >= ord 'a'), ((ord h) <= ord 'z')) = [chr (ord h - 32)] ++ todasMaiusculas t
   | otherwise = [h] ++ todasMaiusculas t

-- 35
-- A FAZER

-- 36
seleciona :: [a] -> [Int] -> [a]
seleciona [] _ = []
seleciona lista (h:t) = [elemento lista h] ++ seleciona lista t
