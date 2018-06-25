import Data.List


-- retornaSup feito com compreensão de listas
retornaSupLista :: Int -> [Int] -> [Int]
retornaSupLista busca lista = [ x | x <- lista, x > busca]

--essa eh a melhor pt d aula uhuuhuhuhu
isPrime :: Int -> Bool
isPrime 1 = False
isPrime 2 = True
isPrime n | (length [ x | x <- [ 2 .. n-1 ], mod n x == 0 ] ) > 0 = False
          | otherwise = True


-- OrdenacaoProgramador
-- import Data.List (está na primeira linha)
type Nome = String
type Linguagem = String
data Pessoa = Programador Nome Linguagem
                deriving (Show, Eq, Ord)
                --deriving (Eq, Ord)
                --deriving (Show, Ord)

programador1 = Programador "Larry" "Perl"
programador2 = Programador "Guido" "Python"
programador3 = Programador "Bjarne" "C++"

lista = [ programador1, programador2, programador3 ]

ordenado = sort lista
