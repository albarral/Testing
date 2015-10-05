package util;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.nio.charset.Charset;
import java.text.ParseException;
import java.util.Properties;

/**
 *
 * @author JRB20081106
 */

abstract public class ConfigFile
{
	public class ConfigException extends Exception
	{
		public ConfigException(String msg)
		{
			super (msg);
		}
		public ConfigException(String msg, Throwable cause)
		{
			super (msg, cause);
		}
		public ConfigException(Throwable cause)
		{
			super (cause);
		}
	}

	private File _cfgFile;
	private Properties _cfgFileProps;

	protected ConfigFile(String cfgFilePath) throws Exception
	{
		File cfgFile = new File(cfgFilePath);
		init(cfgFile);
	}

	protected ConfigFile(File cfgFile) throws Exception
	{
		init(cfgFile);
	}

	private void init(File cfgFile) throws Exception
	{
		_cfgFile = cfgFile;
		_cfgFileProps = getProperties(cfgFile);
		readInParameters();
	}

	abstract protected void readInParameters() throws Exception;

	private Properties getProperties(File cfgFile) throws IOException
	{
		Properties props = new Properties();
		if (!cfgFile.canRead())
		{
			throw new IOException("Couldn't find configuration file: " + cfgFile.getCanonicalPath());
		}
		FileInputStream in = new FileInputStream(cfgFile);
		props.load(in);
		in.close();
		return props;
	}

	public File getCfgFile()
	{
		return _cfgFile;
	}

	public String getStringParam(String key) throws ConfigException
	{
		String value = _cfgFileProps.getProperty(key);
		if (value == null)
		{
			throw new ConfigException("Parameter not found: " + key);
		}
		return value;
	}

	//different values are split by the commas:
	public String[] getStringArrayParam(String key) throws ConfigException
	{
		String groupValue = _cfgFileProps.getProperty(key);
		if (groupValue == null)
		{
			throw new ConfigException("Parameter not found: " + key);
		}
		return groupValue.split(",");
	}

	public int getIntParam(String key) throws ConfigException
	{
		String strValue = getStringParam(key);
		return Integer.parseInt(strValue);
	}

	//different values are split by the commas:
	public int[] getIntArrayParam(String key) throws ConfigException
	{
		String[] strArray = getStringArrayParam(key);
		int[] intArray = new int[strArray.length];
		for (int i=0; i<intArray.length; i++)
		{
			intArray[i] = Integer.parseInt(strArray[i]);
		}
		return intArray;
	}

	public long getLongParam(String key) throws ConfigException
	{
		String strValue = getStringParam(key);
		return Long.parseLong(strValue);
	}

	public int getIntHexParam(String key) throws ConfigException
	{
		String strValue = getStringParam(key);
		if (strValue.startsWith("0x")) { strValue = strValue.substring(2); }
		return Integer.parseInt(strValue, 16);
	}

	public boolean getBooleanParam(String key) throws ConfigException
	{
		boolean value = false;
		String strValue = getStringParam(key);
		if (strValue.equals("Y"))
		{
			value = true;
		}
		else if (strValue.equals("N"))
		{
			value = false;
		}
		else
		{
			throw new ConfigException("Invalid boolean value (" + strValue + ") for parameter " + key + "." +
					" Accepted values (Y/N)");
		}
		return value;
	}

	public boolean getBooleanParam(String key, boolean defaultValue) throws ConfigException
	{
		boolean value = defaultValue;
		String strValue = _cfgFileProps.getProperty(key);
		if (strValue != null)	//use value provided
		{
			value = getBooleanParam(key);
		}
		// else 	//param not found -> use default value
		return value;
	}

	public boolean getOptionalBooleanParam(String key) throws ConfigException
	{
		return getBooleanParam(key, false);
	}


	public File getFileParam(String key) throws ConfigException
	{
		String strValue = getStringParam(key);
		return new File(strValue);
	}


	public Charset getCharsetParam(String key) throws ConfigException
	{
		String strValue = getStringParam(key);
		return Charset.forName(strValue);
	}

	public int getIpPortNumParam(String key) throws ConfigException
	{
		int port = getIntParam(key);
		if (port < 0 || 65535 < port)
		{
			throw new ConfigException("Invalid port value (" + port + ") for parameter " + key);
		}
		return port;
	}

	public URL getUrlParam(String key) throws ConfigException
	{
		URL url = null;
		String strValue = getStringParam(key);
		try
		{
			url = new URL(strValue);
		}
		catch (MalformedURLException mue)
		{
			throw new ConfigException(mue);
		}
		return url;
	}

}
