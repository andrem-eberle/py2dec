__doc__ = 'Make the custom certificate and private key files used by test_ssl\nand friends.'
import os
import shutil
import sys
import tempfile
from subprocess import '*',
zero atom IMPORT_STAR
req_template = '\n    [req]\n    distinguished_name     = req_distinguished_name\n    x509_extensions        = req_x509_extensions\n    prompt                 = no\n\n    [req_distinguished_name]\n    C                      = XY\n    L                      = Castle Anthrax\n    O                      = Python Software Foundation\n    CN                     = {hostname}\n\n    [req_x509_extensions]\n    subjectAltName         = @san\n\n    [san]\n    DNS.1 = {hostname}\n    {extra_san}\n\n    [dir_sect]\n    C                      = XY\n    L                      = Castle Anthrax\n    O                      = Python Software Foundation\n    CN                     = dirname example\n\n    [princ_name]\n    realm = EXP:0, GeneralString:KERBEROS.REALM\n    principal_name = EXP:1, SEQUENCE:principal_seq\n\n    [principal_seq]\n    name_type = EXP:0, INTEGER:1\n    name_string = EXP:1, SEQUENCE:principals\n\n    [principals]\n    princ1 = GeneralString:username\n\n    [ ca ]\n    default_ca      = CA_default\n\n    [ CA_default ]\n    dir = cadir\n    database  = $dir/index.txt\n    crlnumber = $dir/crl.txt\n    default_md = sha256\n    default_days = 3600\n    default_crl_days = 3600\n    certificate = pycacert.pem\n    private_key = pycakey.pem\n    serial    = $dir/serial\n    RANDFILE  = $dir/.rand\n\n    policy          = policy_match\n\n    [ policy_match ]\n    countryName             = match\n    stateOrProvinceName     = optional\n    organizationName        = match\n    organizationalUnitName  = optional\n    commonName              = supplied\n    emailAddress            = optional\n\n    [ policy_anything ]\n    countryName   = optional\n    stateOrProvinceName = optional\n    localityName    = optional\n    organizationName  = optional\n    organizationalUnitName  = optional\n    commonName    = supplied\n    emailAddress    = optional\n\n\n    [ v3_ca ]\n\n    subjectKeyIdentifier=hash\n    authorityKeyIdentifier=keyid:always,issuer\n    basicConstraints = CA:true\n\n    '
here = os.path.abspath(os.path.dirname(__file__))

def make_cert_key(hostname,sign=False,extra_san='',ext='req_x509_extensions_full',key='rsa:3072'):
    print( ( 'creating cert for ' + hostname ))
    tempnames = []
    
    for i in range(3):
        with tempfile.NamedTemporaryFile(delete=False) as f:
            tempnames.append(f.name)
        continue
    req_file, cert_file, key_file = tempnames
    try:
        req = req_template.format(extra_san=extra_san,hostname=hostname)
        with open(req_file, 'w') as f:
            f.write(req)
        args = ['req','-new','-days','3650','-nodes','-newkey','rsa:1024','-keyout',key_file,'-config',req_file]
        
        if sign :
            with tempfile.NamedTemporaryFile(delete=False) as f:
                tempnames.append(f.name)
                reqfile = f.name
            args = (args + ['-out',reqfile])
        else:
            args = (args + ['-x509','-out',cert_file])
        check_call( ['openssl'] + args )
        
        if sign :
            args = ['ca','-config',req_file,'-out',cert_file,'-outdir','cadir','-policy','policy_anything','-batch','-infiles',reqfile]
            check_call( ['openssl'] + args )
        with open(cert_file, 'r') as f:
            cert = f.read()
        with open(key_file, 'r') as f:
            key = f.read()
        return (cert,key)
    finally:
        
        for name in tempnames:
            os.remove(name)
            continue
TMP_CADIR = 'cadir'

def unmake_ca():
    shutil.rmtree(TMP_CADIR)

def make_ca():
    os.mkdir(TMP_CADIR)
    with open(os.path.join('cadir', 'index.txt'), 'a+') as f:
    with open(os.path.join('cadir', 'crl.txt'), 'a+') as f:
        f.write('00')
    with open(os.path.join('cadir', 'index.txt.attr'), 'w+') as f:
        f.write('unique_subject = no')
    with tempfile.NamedTemporaryFile('w') as t:
        t.write(req_template.format(extra_san='',hostname='our-ca-server'))
        t.flush()
        with tempfile.NamedTemporaryFile() as f:
            args = ['req','-new','-days','3650','-extensions','v3_ca','-nodes','-newkey','rsa:3072','-keyout','pycakey.pem','-out',f.name,'-subj','/C=XY/L=Castle Anthrax/O=Python Software Foundation CA/CN=our-ca-server']
            check_call( ['openssl'] + args )
            args = ['ca','-config',t.name,'-create_serial','-out','pycacert.pem','-batch','-outdir',TMP_CADIR,'-keyfile','pycakey.pem','-days','3650','-selfsign','-extensions','v3_ca','-infiles',f.name]
            check_call( ['openssl'] + args )
            args = ['ca','-config',t.name,'-gencrl','-out','revocation.crl']
            check_call( ['openssl'] + args )

if __name__ == '__main__' :
    os.chdir(here)
    cert, key = make_cert_key('localhost')
    with open('ssl_cert.pem', 'w') as f:
        f.write(cert)
    with open('ssl_key.pem', 'w') as f:
        f.write(key)
    print('password protecting ssl_key.pem in ssl_key.passwd.pem')
    check_call(['openssl','rsa','-in','ssl_key.pem','-out','ssl_key.passwd.pem','-des3','-passout','pass:somepass'])
    check_call(['openssl','rsa','-in','ssl_key.pem','-out','keycert.passwd.pem','-des3','-passout','pass:somepass'])
    with open('keycert.pem', 'w') as f:
        f.write(key)
        f.write(cert)
    with open('keycert.passwd.pem', 'a+') as f:
        f.write(cert)
    make_ca()
    cert, key = make_cert_key('fakehostname')
    with open('keycert2.pem', 'w') as f:
        f.write(key)
        f.write(cert)
    cert, key = make_cert_key('localhost', True)
    with open('keycert3.pem', 'w') as f:
        f.write(key)
        f.write(cert)
    cert, key = make_cert_key('fakehostname', True)
    with open('keycert4.pem', 'w') as f:
        f.write(key)
        f.write(cert)
    extra_san = ['otherName.1 = 1.2.3.4;UTF8:some other identifier','otherName.2 = 1.3.6.1.5.2.2;SEQUENCE:princ_name','email.1 = user@example.org','DNS.2 = www.example.org','dirName.1 = dir_sect','URI.1 = https://www.python.org/','IP.1 = 127.0.0.1','IP.2 = ::1','RID.1 = 1.2.3.4.5']
    cert, key = make_cert_key('allsans',extra_san='\n'.join(extra_san))
    with open('allsans.pem', 'w') as f:
        f.write(key)
        f.write(cert)
    unmake_ca()
    print('\n\nPlease change the values in test_ssl.py, test_parse_cert function related to notAfter,notBefore and serialNumber')
    check_call(['openssl','x509','-in','keycert.pem','-dates','-serial','-noout'])
