# facturbot-ocr

Código de Zonal OCR de [FacturBot](https://github.com/javierdemartin/FacturBot).

## Compilación

Para compilar, incluir las librerias de [Leptonica](http://www.leptonica.com/) y [Tesseract](https://github.com/tesseract-ocr/) de la siguiente forma:
```
g++ zonal-ocr.cpp -o zonal-ocr -llept -ltesseract
```

## Uso
El código aplicará un reconocimiento de caracteres sobre un rectángulo de cierto tamaño y situado en unas coordenadas específicas dentro de una imagen. Para ello, el programa lee de la línea de comandos los siguientes datos, en el siguiente orden:
* `<imagen-a-analizar>`: ruta de la imagen sobre la que se aplicará el zonal OCR.
* `<densidad>`: densidad a la que se ha obtenido la imagen a partir del PDF de la factura del usuario.
* `<whitelist>`: caracteres a reconocer en el zonal OCR, es decir, caracteres que pueden existir en dicho rectángulo de la imagen. Por ejemplo: si en una zona solo se espera que haya números, se le pasará como whitelist una cadena con los posibles dígitos: "0123456789".
* `<left>`: píxeles desde la izquierda de la imagen hasta la esquina superior izquierda del rectángulo (a una densidad de 200).
* `<top>`: píxeles desde la parte superior de la imagen hasta la esquina superior izquierda del rectángulo (a una densidad de 200).
* `<width>`: ancho del rectángulo (a una densidad de 200).
* `<height>`: alto del rectángulo (a una densidad de 200).

Las coordenadas serán las correspondientes a la imagen con una densidad de 200. Esto se debe a que las coordenadas de la plantilla de la factura se habrán guardado en nuestra base de datos con esa densidad. En el código del bot se hará primero una consulta a la base de datos para obtener dichas coordenadas e insertarlas como parámetro en la ejecución de la aplicación de zonal OCR. Como la imagen a analizar se ha podido obtener con una densidad mayor, en el código se hace un escalado de `<densidad> / 200` para obtener las coordenadas correspondientes.
