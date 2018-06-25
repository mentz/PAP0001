module Fila where

data Fila t = F [t] deriving (Show)

filaTeste = F[1,2,3,4]

novaFila :: Fila t
novaFila = F[]

removerFila :: Fila t -> Fila t
removerFila (F[]) = error "Fila vazia"
removerFila (F(h:t)) = F t

frente :: Fila t -> t
frente (F[]) = error "Fila vazia"
frente (F(h:t)) = h

inserirFila :: Fila t -> t -> Fila t
inserirFila (F lista) n = F(lista ++ [n])

filaVazia :: Fila t -> Bool
filaVazia (F[]) = True
filaVazia _ = False
