module Funcoes where

par :: Int -> Bool
par n | (mod n 2 == 0) = True
      | otherwise = False

impar :: Int -> Bool
impar n = not (par n)
