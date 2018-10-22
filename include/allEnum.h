#ifndef ALLENUM_H_INCLUDED
#define ALLENUM_H_INCLUDED

enum entType //rajoutez toujour les nouveau type a la fin (avant l'element last), ensuite il faut aussi les ajouter a la fin de l'instantation de la classe en dessous (entityStdStorage), et les initialiser de maniere standart dans le init du .cpp
{
    player, //un mob: une boule de feu destructristrice et invincible,a la capacité de load la map
    zombie, //actuellement indisponible
    dropeditem,

    last //c'est un element system de l'enum  qui sert a connaitre le nombre d'entité qui existent dans l'enum, ne pas modifier ni rien rajouter aprés
    //pour info, dans le EntityStdStorage::storageEntity[last] il y a une entity de type entityError qui est return en cas de request d'une entity qui existe pas
};

#endif // ALLENUM_H_INCLUDED
