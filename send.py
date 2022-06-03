import ftplib
import logging


def ftp_upload(hostname, username, password, port, upload_src_path, upload_dst_path, timeout):
    logger.info({
        'action': 'ftp_upload',
        'status': 'run'
    })
    # FTP接続/アップロード
    with ftplib.FTP() as ftp:
        try:    
            ftp.connect(host=hostname, port=port, timeout=timeout)
            # パッシブモード設定
            ftp.set_pasv("true")
            # FTPサーバログイン
            ftp.login(username, password)
            with open(upload_src_path, 'rb') as fp:
                ftp.storbinary(upload_dst_path, fp)

        except ftplib.all_errors as e:
            logger.error({
                'action': 'ftp_upload',
                'message': 'FTP error = %s' % e
            })
    logger.info({
        'action': 'ftp_upload',
        'status': 'success'
    })


# logの設定
logger = logging.getLogger(__name__)
formatter = '%(asctime)s:%(name)s:%(levelname)s:%(message)s'
logging.basicConfig(
    filename='./ftp_logger.log',
    level=logging.DEBUG,
    format=formatter
)
logger.setLevel(logging.INFO)

# 接続先サーバーのホスト名
hostname = "192.168.3.16" 
# アップロードするファイルパス
upload_src_path = "./AnimalBytes.3gx" 
# アップロード先のファイルパス（STORはファイルをアップロードするためのFTPコマンドなので必要です。）
upload_dst_path = "STOR /luma/plugins/0004000000086200/AnimalBytes.3gx" 
# サーバーのユーザー名
username = "" 
# サーバーのログインパスワード
password = "" 
# FTPサーバポート
port = 5000
timeout = 500

logger.info("===START FTP===")
ftp_upload(hostname, username, password, port, upload_src_path, upload_dst_path, timeout)
logger.info("===FINISH FTP===")
