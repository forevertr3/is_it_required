# is_it_required

    Kayıpsız (Loseless) resim formatlarını (tga, png vs.) yine kayıpsız olarak sıkıştırmaya yönelik bir çalışmadır. Resmin formatı değişmekte, ve resmin zçılabilmesi için geri çevirlesi gerekmektedir.
    
    SDL2 ile arayüz oluşmaktadır. Mingw için kullanım, VB'de daha kolay sanırım.
    INC: SDL2/include/SDL.H
    LIB: SDL2/LIB
    BIN: *.dll' leri projeye ekle veya system32'ye atın.
    Dinamik Bağlama için: -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx ekleyiniz. 
    
    Open File Dialog için libcommdlg32 'yi de ekleyiniz.
    Data Klöründekileri de kodların bulunduğu ana dizine çıkartınız
    
