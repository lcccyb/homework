import java.security.*;
import java.io.*;
import java.security.cert.*;
import java.security.cert.Certificate;

public class X509 {
	public static void main(String[] args) throws IOException {
		//构建对象
		CertificateFactory fac;
		try {
			//文件流读入证书
			FileInputStream test = new FileInputStream("C:/Users/lcccy/Desktop/test.cer");
			//实例化
			fac = CertificateFactory.getInstance("X.509");
			//生成证书
		    Certificate c = fac.generateCertificate(test);
		    //类型强制转换
		    X509Certificate t = (X509Certificate)c;
		    //读取完成
		    test.close();
		    
		    String s = c.toString();
		    //总体X509信息
		    System.out.println("输出证书信息:\n" + s + "\n");
		    System.out.println("版本号:" + t.getVersion());
		    System.out.println("序列号:" + t.getSerialNumber().toString(16));
		    System.out.println("签发者:" + t.getIssuerDN());
		    System.out.println("有效起始日期:" + t.getNotBefore());
		    System.out.println("有效终止日期:" + t.getNotAfter());
		    System.out.println("主体名:" + t.getSubjectDN());
		    System.out.println("签名算法:" + t.getSigAlgName());
		    System.out.println("签名:" + t.getSignature().toString());
		    PublicKey key = t.getPublicKey();
		    byte [] code = key.getEncoded();  
		    System.out.println("公钥:");
		    for(int i = 0; i < code.length; i++) {
		    	System.out.print(code[i] + ",");
		    	if((i + 1) % 20 == 0) {
		    		System.out.println();
		    	}
		    }
		    System.out.println();
		} 
		catch (CertificateException e) {
			e.printStackTrace();
		}
	}

}
