module Teste where

import Fila 
import System.IO

mostra_fila :: Fila t -> [t]
mostra_fila fila | (filaVazia fila) = []
                 | otherwise = (frente fila):(mostra_fila (removerFila fila))


main :: IO()
main =  do
			putStr "Digite o primeiro número"
			n1 <- getline
			putStr "Digite o segundo número"
			n2 <- getline
			putStr "Soma: " ++ (show( (read n1) + read(n2))) ++ "\n"


get char :: IO()
get char  = do
			putStr "Digite um caracter"
			c <- getChar
			putStr "O caractere foi: "
			putChar c


-- tem que dar import system.I
escrever :: IO()
escrever = do
			fd <- openfile "/tmp/teste.txt" WriteMode
			hPutStr fd "Escrita no arquivo....."
			putStrLn "Escrita realizada com sucesso"
			hFlush fd
			hClose fd

apendar :: IO()
apendar = do
			fd <- openfile "/tmp/teste.txt" AppendMode
			hPutStr fd "Nova escrita no arquivo....."
			putStrlN "Escrita realizada com sucesso"
			hFlush fd
			hClose fd

ler_arquivo :: IO()
ler_arquivo = do
				fd <- openFile "/tmp/teste.txt" ReadMode
				content <- hGetContents fd
				putStrLn content
				hClose fd

---TESTE LET, UTILIZADA PARA FAZER DEFINIÇÕES TEMPORÁRIAS
type Nome = String 
type Idade = Int
type CPF = String

data Pessoa = Pessoa Nome Idade CPF
				deriving( Show )


---ENUMERAÇAO
data dia = Domingo
           | Segunda
		   | Terca
		   | Quarta 
		   | Quinta
		   | Sexta 
		   | Sabado
		       deriving(Show, Eq)

dia :: Int -> Dia
dia num = do 
			( num == 0 ) = Domingo
