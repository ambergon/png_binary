


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main( int argc, char* argv[] ) {


    // 引数
    if ( argc != 2 ){
        return 0;
    }



    const char *filename = argv[1];
    // const char *filename = "a.png";
    FILE *file;
    unsigned char *buffer;
    size_t file_size;

    // PNGファイルをバイナリモードで開く
    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("ファイルを開けませんでした");
        return 0;
    }

    // ファイルのサイズを取得
    fseek(file, 0, SEEK_END); 
    // 現在の位置を取得（ファイルサイズ）
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // ファイルサイズが26バイト以下なら終了
    if (file_size < 26) {
        return 0;
    }

    // バッファを確保
    buffer = (unsigned char *)malloc( file_size );
    if (buffer == NULL) {
        perror("メモリ確保に失敗しました");
        fclose(file);
        return 0;
    }

    // ファイルを読み込む
    size_t bytes_read = fread(buffer, 1, file_size, file);
    if (bytes_read != file_size) {
        perror("ファイルの読み込みに失敗しました");
        free( buffer );
        fclose( file );
        return 0;
    }

    // // 読み込んだデータを表示（16進数形式）
    // for ( size_t i = 0 ; i < file_size ; i++ ) {
    //     printf( "%02X" , buffer[i] );
    //     // 16バイトごとに改行
    //     if ((i + 1) % 16 == 0) {
    //         printf("\n");
    //     }
    // }

    // 最初の12byteでPNGかどうかチェック
    unsigned char check[13];
    // その後のIHDRを取得
    unsigned char res[14];

    memcpy( check , buffer, 12);
    // 89 50 4E 47 0D 0A 1A 0A 00 00 00 0Dに対応する配列
    unsigned char top_signature[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0x00, 0x00, 0x00, 0x0D};

    // 配列の比較
    // 指定されたバイト列で始まらない。
    if ( memcmp( check , top_signature, sizeof( top_signature ) ) != 0) {
        return 0;
    }

    memcpy( res , buffer + 12 , 13); 
    for (int i = 0; i < 13; i++ ) {
        printf("%02X ", res[i]);
    }
    // printf("\n");


    // リソースを解放
    free( buffer );
    fclose( file );

    return EXIT_SUCCESS;
}











