# Issue #9: GUI HP jugador y enemigos.
## Ignacio Delgadillo Vera Rol: 2503020-6

Se realizaron 3 cambios en el archivo  draw.c :

:bulb: Se agregó la muestra gráfica del HP restante del jugador y los enemigos con una barra que va disminuyendo en tamaño y cambiando de color hasta morir junto con la entidad, limitada ya que una bullet quitaba mucho HP, o lo contrario, que  el HP era limitado.

:bulb: Se agregó una mira que siempre está mostrando donde el esta apuntando el jugador mediante el mousse.

:bulb: Por último se agregó un punto que cambia de color cuando cooldown llega a cero, el problema es que en un principio pense que se trataba de un cooldown de bloquear el arma por un tiempo para esperar enfriamiento, pero en realidad esa variable solo separa el tiempo de disparo de cada bala, por lo que el punto solo cambia de color cada vez que dispara, no se si es error del juego o la version que cloné estaba mala.

